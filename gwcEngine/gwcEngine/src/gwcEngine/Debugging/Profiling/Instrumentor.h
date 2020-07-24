#pragma once
#include <fstream>

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
private:
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
    std::mutex m_resBlock;
public:
    Instrumentor()
        : m_CurrentSession(nullptr), m_ProfileCount(0)
    {
    }

    void BeginSession(const std::string& name, const std::string& filepath = "results.json")
    {
        m_OutputStream.open(filepath);
        WriteHeader();
        m_CurrentSession = new InstrumentationSession{ name };
    }

    void EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_ProfileCount = 0;
    }

    void WriteProfile(const ProfileResult& result)
    {
        std::lock_guard<std::mutex> lock(m_resBlock);
        if (m_ProfileCount++ > 0)
            m_OutputStream << "," << std::endl;

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_OutputStream << "{" << std::endl;
        m_OutputStream << "    \"cat\":\"function\"," << std::endl;
        m_OutputStream << "    \"dur\":" << (result.End - result.Start) << ',' << std::endl;
        m_OutputStream << "    \"name\":\"" << name << "\"," << std::endl;
        m_OutputStream << "    \"ph\":\"X\"," << std::endl;
        m_OutputStream << "    \"pid\":0," << std::endl;
        m_OutputStream << "    \"tid\":" << result.ThreadID << "," << std::endl;
        m_OutputStream << "    \"ts\":" << result.Start << std::endl;
        m_OutputStream << "}";

        m_OutputStream.flush();
    }

    void WriteHeader()
    {
        std::lock_guard<std::mutex> lock(m_resBlock);
        m_OutputStream << "{\"otherData\": {},"<< std::endl<<"\"traceEvents\":[" << std::endl;
        m_OutputStream.flush();
    }

    void WriteFooter()
    {
        std::lock_guard<std::mutex> lock(m_resBlock);
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }

    static Instrumentor& Get()
    {
        static Instrumentor instance;
        return instance;
    }
};

class InstrumentationTimer
{
public:
    InstrumentationTimer(const char* name)
        : m_Name(name), m_Stopped(false)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~InstrumentationTimer()
    {
        if (!m_Stopped)
            Stop();
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

        m_Stopped = true;
    }
private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};

#if GE_PROFILING
#define PROFILE_BEGIN_SESSION(name,filePath) ::Instrumentor::Get().BeginSession(name,filePath)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#define PROFILE_SCOPE(name) ::InstrumentationTimer timer##__LINE__(name);
#define PROFILE_END_SESSION() ::Instrumentor::Get().EndSession()
#else
#define PROFILE_BEGIN_SESSION(name,filePath)
#define PROFILE_FUNCTION() 
#define PROFILE_SCOPE(name) 
#define PROFILE_END_SESSION() 
#endif // Profiling macros


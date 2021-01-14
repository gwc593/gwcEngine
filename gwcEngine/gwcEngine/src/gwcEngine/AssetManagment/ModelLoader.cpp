#include"gepch.h"
#include "ModelLoader.h"
#include "gwcEngine/Components/Physics/Transform.h"
#include "gwcEngine/Components/Render/MeshRenderer.h"
#include "gwcEngine/Renderer/Material.h"


namespace gwcEngine
{
	struct COLLADA_MeshData
	{
		std::string ID;
		std::string Name;
		std::pair<int, float*> Positions;
		std::pair<int, float*> Normals;
		std::pair<int, float*> UVs;
		std::pair<int, int*> Indicies;
		int Triangles;

		COLLADA_MeshData()
		{
			Positions.first = 0;
			Positions.second = nullptr;

			Normals.first = 0;
			Normals.second = nullptr;

			UVs.first = 0;
			UVs.second = nullptr;

			Indicies.first = 0;
			Indicies.second = nullptr;
		}

		COLLADA_MeshData(COLLADA_MeshData&& other)
		{
			ID = other.ID;
			Name = other.Name;
			
			Positions.first = other.Positions.first;
			Positions.second = other.Positions.second;
			other.Positions.second = nullptr;

			Normals.first = other.Normals.first;
			Normals.second = other.Normals.second;
			other.Normals.second = nullptr;

			UVs.first = other.UVs.first;
			UVs.second = other.UVs.second;
			other.UVs.second = nullptr;

			Indicies.first = other.Indicies.first;
			Indicies.second = other.Indicies.second;
			other.Indicies.second = nullptr;

			Triangles = other.Triangles;

		}

		~COLLADA_MeshData()
		{
			if (Positions.second != nullptr) {
				free(Positions.second);
				Positions.second = nullptr;
			}

			if (Normals.second != nullptr) {
				free(Normals.second);
				Normals.second = nullptr;
			}

			if (UVs.second != nullptr) {
				free(UVs.second);
				UVs.second = nullptr;
			}

			if (Indicies.second != nullptr) {
				free(Indicies.second);
				Indicies.second = nullptr;
			}
		}
	};

	struct COLLADA_NetworkNode
	{
		COLLADA_NetworkNode* parent = nullptr;
		std::vector<COLLADA_NetworkNode*> Children;
		float TransformData[4][4] = { 0 };
	};

	void printStructure(TiXmlElement* parent, int level = 0)
	{
		for (int i = 0; i < level; i++)
			printf("   ");

		if(level!=0)
			printf("|--");
		printf("%s\n", parent->Value());

		for (TiXmlElement* elem = parent->FirstChildElement(); elem; elem = elem->NextSiblingElement()) {
			printStructure(elem,level+1);
		}
	}

	TiXmlElement* GetElement(TiXmlElement* root, const char* value)
	{
		if (!std::strcmp(root->Value(), value)) {
			return root;
		}

		TiXmlElement* ret = nullptr;

		for (TiXmlElement* elem = root->FirstChildElement(); elem; elem = elem->NextSiblingElement()) {
			ret = GetElement(elem, value);
			if (ret)
				return ret;
		}

		return nullptr;
	}

	COLLADA_MeshData ParseGeometry(TiXmlElement* geom)
	{
		COLLADA_MeshData ret;
		TiXmlElement* mesh = geom->FirstChildElement("mesh");

		//Get ID
		geom->QueryStringAttribute("id", &(ret.ID));
		
		//Get name
		geom->QueryStringAttribute("name", &(ret.Name));

		//get number of triangles
		mesh->FirstChildElement("triangles")->QueryIntAttribute("count", &(ret.Triangles));
		
		//set number of indicies size
		ret.Indicies.first = ret.Triangles*3*3;
		ret.Indicies.second = (int*)calloc(ret.Indicies.first, sizeof(int));

		{
			std::string valuesRaw = mesh->FirstChildElement("triangles")->FirstChildElement("p")->GetText();
			std::stringstream stream(valuesRaw);
			int n;
			int i = 0;
			while (stream >> n) {
				ret.Indicies.second[i] = n;
				++i;
			}
		}

		//parse vertex data
		TiXmlElement* positions = nullptr;
		TiXmlElement* normals = nullptr;
		TiXmlElement* uvs = nullptr;

		//get positions element
		for (auto elem = mesh->FirstChildElement("source"); elem; elem = elem->NextSiblingElement()) {
			if (!std::strcmp(elem->Value(), "source")) {
				auto id = std::string(elem->Attribute("id"));
				auto comp = std::string(ret.ID + "-positions");
				if (id == comp) {
					positions = elem;
					break;
				}
			}
		}
		
		//set number of positions
		positions->FirstChildElement("float_array")->QueryIntAttribute("count", &(ret.Positions.first));
		ret.Positions.second = (float*)calloc(ret.Positions.first,sizeof(float));

		{
			std::string valuesRaw = positions->FirstChildElement("float_array")->GetText();
			std::stringstream stream(valuesRaw);
			float n;
			int i = 0;
			while (stream >> n) {
				ret.Positions.second[i] = n;
				++i;
			}
		}

		//get normals element
		for (auto elem = mesh->FirstChildElement("source"); elem; elem = elem->NextSiblingElement()) {
			if (!std::strcmp(elem->Value(), "source")) {
				auto id = std::string(elem->Attribute("id"));
				auto comp = std::string(ret.ID + "-normals");
				if (id == comp) {
					normals = elem;
					break;
				}
			}
		}
		
		//set number of normals
		normals->FirstChildElement("float_array")->QueryIntAttribute("count", &(ret.Normals.first));
		ret.Normals.second = (float*)calloc(ret.Normals.first, sizeof(float));

		{
			std::string valuesRaw = normals->FirstChildElement("float_array")->GetText();
			std::stringstream stream(valuesRaw);
			float n;
			int i = 0;
			while (stream >> n) {
				ret.Normals.second[i] = n;
				++i;
			}
		}

		//get uvs element
		for (auto elem = mesh->FirstChildElement("source"); elem; elem = elem->NextSiblingElement()) {
			if (!std::strcmp(elem->Value(), "source")) {
				auto id = std::string(elem->Attribute("id"));
				auto comp = std::string(ret.ID + "-map-0");
				if (id == comp) {
					uvs = elem;
					break;
				}
			}
		}
		
		//set number of uvs
		uvs->FirstChildElement("float_array")->QueryIntAttribute("count", &(ret.UVs.first));
		ret.UVs.second = (float*)calloc(ret.UVs.first, sizeof(float));
		{
			std::string valuesRaw = uvs->FirstChildElement("float_array")->GetText();
			std::stringstream stream(valuesRaw);
			float n;
			int i = 0;
			while (stream >> n) {
				ret.UVs.second[i] = n;
				++i;
			}
		}

		if (!(positions && normals && uvs)) {
			GE_CORE_ERROR("Corrupt vertex data on COLLADA model");
		}

		return ret;
	}

	std::unordered_map<std::string, Ref<Mesh>> ParseMeshData(const std::string& path)
	{
		std::vector<COLLADA_MeshData> colData;
		std::unordered_map<std::string, Ref<Mesh>> ret;

		TiXmlDocument doc(path);
		if (!doc.LoadFile()) {
			GE_CORE_WARN("Unable to load COLLADA model: {0}", path);
			return ret;
		}

		TiXmlElement* root = doc.RootElement();
		auto element = GetElement(root, "library_geometries");

		for (TiXmlElement* elem = element->FirstChildElement(); elem; elem = elem->NextSiblingElement()) {
			colData.push_back(ParseGeometry(elem));
		}

		for (auto it = colData.begin(); it != colData.end(); ++it) {
			Ref<Mesh> mesh = CreateRef<Mesh>();
			gwcEngine::BufferLayout layout = {
				{gwcEngine::ShaderDataType::Float3, "a_Position"},
				{gwcEngine::ShaderDataType::Float2, "a_TexCoord"},
				{gwcEngine::ShaderDataType::Float3, "a_Normal"}
			};

			uint32_t totalVertElements =  3 * it->Triangles * (layout.GetStride() / sizeof(float));
			float* vertices = (float*)calloc(totalVertElements,sizeof(float));
			
			for (int i = 0; i < it->Triangles * 3; i++) {
				
				//positions
				for (int p = 0; p < 3; ++p)
					vertices[8 * i + p] = it->Positions.second[p + (it->Indicies.second[i * 3] * 3)];

				//uvs
				for (int u = 0; u < 2; ++u)
					vertices[8 * i + u + 3] = it->UVs.second[u + (it->Indicies.second[i * 3 + 2] * 2)];

				//normals
				for (int n = 0; n < 3; ++n)
					vertices[8 * i + n + 5] = it->Normals.second[n + (it->Indicies.second[i * 3 + 1] * 3)];
			}
			
			mesh->SetVertexBuffer(vertices, sizeof(float)* totalVertElements, layout);
			
			uint32_t vs = it->Triangles * 3;
			uint32_t* inds = (uint32_t*)calloc(vs, sizeof(uint32_t));

			for (uint32_t i = 0; i < vs; ++i) {
				inds[i] = i;
			}



			mesh->SetIndexBuffer(inds, vs, true);

			ret[it->ID] = mesh;

			free(vertices);
			free(inds);
		}



		return ret;

	}

	void ParseNode(TiXmlElement* root, std::unordered_map<std::string, Ref<Mesh>>& meshData, Ref<Transform> parent=nullptr)
	{
		std::string name(root->Attribute("name"));
		auto ent = Entity::Create(name);

		auto transform = ent->AddComponent<Transform>();
		transform->SetParent(parent);

		auto meshRend = ent->AddComponent<MeshRenderer>();
		meshRend->RegisterLayer("Default");
		meshRend->ActivateLayer("Default");

		std::string meshID = root->FirstChildElement("instance_geometry")->Attribute("url");
		meshID.erase(0, 1);

		ent->AddComponent<Mesh>(*meshData[meshID]);
		//set mesh

		ent->AddComponent<Material>();

		//recursive
		for (auto elem = root->FirstChildElement("node"); elem; elem = elem->NextSiblingElement()) {
			if (!std::strcmp(elem->Value(), "node")) {
				
				ParseNode(elem, meshData, transform);
			}
		}
	}

	Ref<Entity> GenetateGameObject(const std::string& path)
	{
		std::unordered_map<std::string, Ref<Mesh>> meshData = ParseMeshData(path);

		TiXmlDocument doc(path);
		if (!doc.LoadFile()) {
			GE_CORE_WARN("Unable to load COLLADA model: {0}", path);
			return Entity::NullEntity;
		}

		TiXmlElement* root = doc.RootElement();
		TiXmlElement* sceneData = GetElement(root, "visual_scene");

		for (auto elem = sceneData->FirstChildElement("node"); elem; elem = elem->NextSiblingElement()) {
			if (!std::strcmp(elem->Value(), "node")) {
				ParseNode(elem, meshData);
			}
		}

		return Entity::NullEntity;
	}
	

	Ref<Entity> ModelLoader::LoadModel(const std::string& path, ModelFormat format)
	{
		Ref<Entity> ret = Entity::NullEntity;

		if (format == ModelFormat::DAE) {
			ret = GenetateGameObject(path);
		}

		return ret;
	}
}
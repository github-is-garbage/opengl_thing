#ifndef ogt_ents
#define ogt_ents

#include <hashmap/map.h>
#include <cglm/types.h>

#include "util.h"

#define MAX_ENTITIES 255

typedef struct Entity_t Entity_t;
typedef void (*CreationFn)(Entity_t* self);
typedef void (*DeletionFn)(Entity_t* self);
typedef void (*ThinkFn)(Entity_t* self, float DeltaTime);
typedef void (*RenderFn)(Entity_t* self, float DeltaTime);

typedef struct
{
	unsigned int VAO;
	unsigned int VBO;

	const char* ModelPath;
	size_t VertexCount;
	size_t MeshCount;
	size_t MaterialCount;
	Material_t* Materials;
	float* Vertices;
} EntityModelInfo_t;

typedef struct
{
	const char* Name;

	EntityModelInfo_t* ModelInfo;

	CreationFn OnCreation;
	DeletionFn OnDeletion;
	ThinkFn Think;
	RenderFn Render;
} EntityClass_t;

struct Entity_t
{
	bool Valid;
	unsigned int Index;

	EntityClass_t* ClassInfo;

	vec3 Origin;
	vec3 Angles;

	CreationFn OnCreation;
	DeletionFn OnDeletion;
	ThinkFn Think;
	RenderFn Render;
};

typedef struct
{
	unsigned int EntIndex;
	Entity_t* Entities[MAX_ENTITIES];
	hashmap* EntityClassMap;

	unsigned int FreeEntIndices[MAX_ENTITIES];
	unsigned int FreeIndexCount;
} EntityManager_t;

extern EntityManager_t EntityManager;

void ogt_init_entity_system(EntityManager_t* Manager);
EntityClass_t* ogt_register_entity_class(const char* Class, CreationFn OnCreation, DeletionFn OnDeletion, ThinkFn Think, RenderFn Render);
EntityClass_t* ogt_find_entity_class(const char* Class);
Entity_t* ogt_create_entity_ex(EntityClass_t* EntityClass);
Entity_t* ogt_create_entity(const char* Class);
void ogt_delete_entity(Entity_t* Entity);
void ogt_think_entities(float DeltaTime);
void ogt_render_entities(float DeltaTime);
void ogt_render_entity_basic(Entity_t* Entity, float DeltaTime); // Renders VAO
void ogt_load_entity_class_model(EntityClass_t* EntityClass);
void ogt_setup_entity_class_model(EntityClass_t* EntityClass, const char* ModelPath);

#endif

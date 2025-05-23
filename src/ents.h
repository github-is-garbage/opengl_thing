#ifndef ogt_ents
#define ogt_ents

#include <hashmap/map.h>
#include <cglm/types.h>

#include "models.h"
#include "physics.h"

#define MAX_ENTITIES 255

typedef struct Entity_t Entity_t;
typedef void (*CreationFn)(Entity_t* self);
typedef void (*DeletionFn)(Entity_t* self);
typedef void (*InitPhysicsFn)(Entity_t* self);
typedef void (*ThinkFn)(Entity_t* self, float DeltaTime);
typedef void (*RenderFn)(Entity_t* self, float DeltaTime);

typedef struct
{
	CreationFn OnCreation;
	DeletionFn OnDeletion;
	InitPhysicsFn InitPhysics;
	ThinkFn Think;
	RenderFn Render;
} EntityCallbacks_t;

typedef struct
{
	const char* Name;

	EntityCallbacks_t* Callbacks;
} EntityClass_t;

struct Entity_t
{
	bool Valid;
	unsigned int Index;

	EntityClass_t* ClassInfo;
	ModelInfo_t* ModelInfo;

	vec3 Origin;
	vec3 Angles;
	vec3 Color;

	dBodyID Body;
	dGeomID Geometry;
};

typedef struct
{
	unsigned int EntIndex;
	Entity_t* Entities[MAX_ENTITIES];
	hashmap* EntityClassMap;
	hashmap* EntityModelMap;

	unsigned int FreeEntIndices[MAX_ENTITIES];
	unsigned int FreeIndexCount;
} EntityManager_t;

void ogt_init_entity_system();
EntityCallbacks_t* ogt_init_entity_callbacks();
EntityClass_t* ogt_register_entity_class(const char* Class, EntityCallbacks_t* Callbacks);
EntityClass_t* ogt_find_entity_class(const char* Class);
Entity_t* ogt_create_entity_ex(EntityClass_t* EntityClass);
Entity_t* ogt_create_entity(const char* Class);
void ogt_delete_entity(Entity_t* Entity);
void ogt_think_entities(float DeltaTime);
void ogt_render_entities(float DeltaTime);
void ogt_render_entity_basic(Entity_t* Entity, float DeltaTime); // Renders VAO
void ogt_set_entity_model(Entity_t* Entity, const char* Path);

#endif

#version 450 		// Use GLSL 4.5

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;
layout(location = 2) in vec2 tex;
layout(location = 3) in vec3 normal;

layout(set = 0, binding = 0) uniform UboViewProjection {
	mat4 projection;
	mat4 view;
} uboViewProjection;

// NOT IN USE, LEFT FOR REFERENCE
layout(set = 0, binding = 1) uniform UboModel {
	mat4 model;
} uboModel;

layout(push_constant) uniform PushModel {
	mat4 model;
} pushModel;

const vec3 DIRECTION_TO_LIGHT = normalize(vec3(30.0, 30.0, 0.0)); // direction to light source
const float AMBIENT = 0.2;

layout(location = 0) out vec3 fragCol;
layout(location = 1) out vec2 fragTex;

void main() {
	gl_Position = uboViewProjection.projection * uboViewProjection.view * pushModel.model * vec4(pos, 1.0);
	
	// only works in certain conditions
	vec3 normalWorldSpace = normalize(mat3(pushModel.model) * normal); // new

	float lightIntensity = AMBIENT + max(dot(normalWorldSpace, DIRECTION_TO_LIGHT), 0);

	fragCol = (lightIntensity * 0.28) * col;
	fragTex = tex;
}
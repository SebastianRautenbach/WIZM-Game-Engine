#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct attrib_info {
	unsigned int layout;
	int size;
	int stride;
	int attrib_length;
};


struct vertex_data {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	int m_BoneIDs[4];
	float m_Weights[4];
};


class core_buffer_object {
public:
	virtual void gen_buffer() {};
	virtual void bind_buffer() {};
	virtual void unbind_buffer() {};
	virtual void destroy_buffer() {};

public:
	GLuint buffer_id;
};


class core_vertex_buffer : public core_buffer_object {
public:
	void gen_buffer() override;
	void bind_buffer() override;
	void unbind_buffer() override;
	void destroy_buffer() override;

	// default constructor 
	core_vertex_buffer(std::vector<vertex_data>& vertices) : mvertices(vertices) {gen_buffer();}
	
public:
	std::vector<vertex_data> mvertices;

};


class core_index_buffer : public core_buffer_object {
public:
	void gen_buffer() override;
	void bind_buffer() override;
	void unbind_buffer() override;
	void destroy_buffer() override;

	// default constructor 
	core_index_buffer(std::vector<unsigned int>& indices) : mindices(indices) {gen_buffer();}

public:
	std::vector<unsigned int> mindices;
};



class core_arr_vertex_buffer : public core_buffer_object {
	
public:
	// default constructor
	core_arr_vertex_buffer(std::vector<vertex_data>& vertices, std::vector<unsigned int>& indices);
	
	void create_buffer();
	void draw_buffer(unsigned int size_of_row);
	void bind_buffer() override;
	void unbind_buffer() override;
	void destroy_buffer() override;
	void create_attrib_arr(unsigned int layout, int size, int stride, int attrib_length);

public:
	core_index_buffer* ibo;
	core_vertex_buffer* vbo;
	std::vector<attrib_info> vertex_attribs;
	
};


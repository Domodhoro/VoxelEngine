#ifndef SHADER_HPP
#define SHADER_HPP

class Shader {
public:
    Shader(const char *vertex_shader_source, const char *fragment_shader_source) {
        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER), fragment = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertex, 1, &vertex_shader_source, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if (!success) {
        	char info_log[512];
        	
            glGetShaderInfoLog(vertex, 512, nullptr, info_log);

            std::cerr << info_log << std::endl;
        }

        glShaderSource(fragment, 1, &fragment_shader_source, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        
        if (!success) {
        	char info_log[512];

            glGetShaderInfoLog(fragment, 512, nullptr, info_log);

            std::cerr << info_log << std::endl;
        }

        shader = glCreateProgram();

        glAttachShader(shader, vertex);
        glAttachShader(shader, fragment);
        glLinkProgram(shader);
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success) {
        	char info_log[512];

            glGetProgramInfoLog(shader, 512, nullptr, info_log);

            std::cerr << info_log << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() const {
        glUseProgram(shader);
    }

    void set_bool(const char *name, bool value) const { 
        glUniform1i(glGetUniformLocation(shader, name), static_cast<int>(value));
    }

    void set_int(const char *name, int value) const { 
        glUniform1i(glGetUniformLocation(shader, name), value); 
    }

    void set_float(const char *name, float value) const { 
        glUniform1f(glGetUniformLocation(shader, name), value);
    }

    void set_vec2(const char *name, const glm::vec2 value) const { 
        glUniform2fv(glGetUniformLocation(shader, name), 1, glm::value_ptr(value));
    }

    void set_vec3(const char *name, const glm::vec3 value) const { 
        glUniform3fv(glGetUniformLocation(shader, name), 1, glm::value_ptr(value)); 
    }

    void set_vec4(const char *name, const glm::vec4 value) const { 
        glUniform4fv(glGetUniformLocation(shader, name), 1, glm::value_ptr(value)); 
    }

    void set_mat2(const char *name, const glm::mat2 matrix) const { 
        glUniformMatrix2fv(glGetUniformLocation(shader, name), 1, false, glm::value_ptr(matrix));
    }

    void set_mat3(const char *name, const glm::mat3 matrix) const { 
        glUniformMatrix3fv(glGetUniformLocation(shader, name), 1, false, glm::value_ptr(matrix));
    }

    void set_mat4(const char *name, const glm::mat4 matrix) const { 
        glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, false, glm::value_ptr(matrix));
    }
protected:
    unsigned int shader = 0u;
    int success = 0;
};

#endif
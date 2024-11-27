#version 150

in vec4 vPosition;

// Uniform variables
uniform vec4 uFaceColour;
uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uView;

// Output to fragment shader
out vec4 vColour;

void main()
{
    gl_Position = uProjection * uView * uModel * vPosition;
    vColour = uFaceColour;
}

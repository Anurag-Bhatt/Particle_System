#version 330 core

// --- PER VERTEX DATA (From QuadVBO) ---
layout (location = 0) in vec3 a_Pos;      // The shape of the quad (centered at 0,0)
layout (location = 1) in vec2 a_TexCoord; // UVs (0,0 to 1,1)

// --- PER INSTANCE DATA (From InstanceVBO) ---
layout (location = 2) in vec3 i_Position; 
layout (location = 3) in vec4 i_Color;
layout (location = 4) in float i_Size;
layout (location = 5) in float i_Rotation;

out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    float c = cos(i_Rotation);
    float s = sin(i_Rotation);
    mat2 rot = mat2(c, s, -s, c);

    vec2 rotatedPos = rot * (a_Pos.xy * i_Size);
    
    vec3 worldPos = i_Position + vec3(rotatedPos, 0.0);

    gl_Position = u_Projection * u_View * vec4(worldPos, 1.0);

    v_TexCoord = a_TexCoord;
    v_Color = i_Color;
}
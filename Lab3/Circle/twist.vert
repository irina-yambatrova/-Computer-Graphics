
vec2 GetCoordinate(float x)
{
	return vec2( cos(x), sin(x) );
}

void main()
{
   vec2 coord = GetCoordinate(gl_Vertex.x);
    vec4 circleCoord = vec4(
        coord.x,
        coord.y,
        gl_Vertex.z,
        gl_Vertex.w
    );
    vec4 position = gl_ModelViewProjectionMatrix * circleCoord;
    // Transform coordinate
    gl_Position = position;
    gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);
}


uniform float TWIST;

float GetSurfaceY(float x, float y, float step)
{
	return mix(x * x + y * y, x * x - y * y, step);
}

vec4 GetSurfaceVertex(float x, float y, float w, float step)
{
	return vec4(x, GetSurfaceY(x, y, step), y, w);
}

void main()
{ 
	float stage = TWIST ;

    vec4 twistedCoord = GetSurfaceVertex(gl_Vertex.x, gl_Vertex.y, gl_Vertex.w, stage);
	
	vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
	// Transform twisted coordinate
    gl_Position = position;
    gl_FrontColor = (position + vec4(1.0)) * 0.5;
}
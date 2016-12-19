

bool PointIsInCircle(vec2 center, float radius, vec2 point)
{
	return pow(point.x - center.x, 2) +  pow(point.y - center.y, 2) <= pow(radius, 2);
}

void main()
{
    vec2 pos = gl_TexCoord[0].xy;
    if (PointIsInCircle(vec2(8.f, 8.f), 4.f, pos) && !PointIsInCircle(vec2(8.f, 8.f), 3.f, pos))
    {
        gl_FragColor = vec4(0.0);
    }
	else
	{
		gl_FragColor = vec4(1.0);
	}
}

uniform vec4 u;
varying vec4 v;
void main()
{
	gl_Position = max(u, v);
}

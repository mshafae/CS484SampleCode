varying vec4 color;

varying vec3 N;
varying vec3 V;

void main(){
  V = vec3(gl_ModelViewMatrix * gl_Vertex);
  N = normalize(gl_NormalMatrix * gl_Normal);
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
  vec3 lightPosition = vec3(1.25, 1.25, 0.5);
  vec3 L = normalize(lightPosition - V);
  vec3 E = normalize(-V);
  vec3 R = normalize(reflect(-L, N)); 

  vec3 P = vec3(1.0, 2.0, 20.0);
  vec3 W = vec3(1.0, 1.0, 1.0);

  color.r = W.x * pow(((max(dot(N,L), 0.0) + 1.0) / 2.0), P.x);
  color.g = W.y * pow(((max(dot(N,L), 0.0) + 1.0) / 2.0), P.y);
  color.b = W.z * pow(((max(dot(N,L), 0.0) + 1.0) / 2.0), P.z);
}


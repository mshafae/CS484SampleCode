#version 120
/*
 * Michael Shafae
 * mshafae at fullerton.edu
 * 
 * A simple Gouraud shader with one light source.
 * This file is the vertex shader which calculates
 * the the vector to the light, the vector to the viewer,
 * and the reflection vector. The color is calculated
 * using the Phong illumination equation.
 *
 * For more information see:
 *     <http://en.wikipedia.org/wiki/Gouraud_shading>
 *
 * $Id: blinn_phong.frag.glsl 4891 2014-04-05 08:36:23Z mshafae $
 *
 * Be aware that for this course, we are limiting ourselves to
 * GLSL v.1.2. This is not at all the contemporary shading
 * programming environment, but it offers the greatest degree
 * of compatability.
 *
 * Please do not use syntax from GLSL > 1.2 for any homework
 * submission.
 *
 */

uniform vec4 light2_position;

// out
varying vec4 myColor;

void main( ){
  vec4 ambientMaterial = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 diffuseMaterial = vec4(1.0, 1.0, 1.0, 1.0);
  vec4 specularMaterial = vec4(0.0, 0.0, 1.0, 1.0);
  float specularPower = 4.0;
  
	// Transforming The Vertex
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// Transforming The Normal To ModelView-Space
	vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
  vec3 viewer = vec3(gl_ModelViewMatrix * gl_Vertex);
  vec3 _light_position = light2_position.xyz / light2_position.w;
  vec3 light = normalize(_light_position - viewer);
  vec3 eye = normalize(-viewer);
  vec3 reflection = normalize(reflect(-light, normal));
  
	// Transforming The Vertex Position To ModelView-Space
	vec4 vertex_in_modelview_space = gl_ModelViewMatrix * gl_Vertex;

  vec4 ambient = vec4(0.2, 0.0, 0.0, 1.0);
  vec4 diffuse = clamp(diffuseMaterial * max(dot(normal, light), 0.0), 0.0, 1.0);
  vec4 specular = clamp(specularMaterial * pow(max(dot(reflection, eye), 0.0), specularPower), 0.0, 1.0);
  myColor = ambient + diffuse + specular;
}

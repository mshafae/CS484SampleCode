#version 120
/*
 * Michael Shafae
 * mshafae at fullerton.edu
 * 
 * A simple Gouraud shader with two light sources.
 * This file is the vertex shader which calculates
 * the the vector to the light, the vector to the viewer,
 * and the reflection vector. The color is calculated
 * using the Phong illumination equation.
 *
 * For more information see:
 *     <http://en.wikipedia.org/wiki/Gouraud_shading>
 *
 * $Id: gouraud.vert.glsl 5717 2015-04-15 17:31:49Z mshafae $
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

// These are passed in from the CPU program, camera_control_*.cpp
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;
uniform vec4 light0_position;
uniform vec4 light0_color;
uniform vec4 light1_position;
uniform vec4 light1_color;

// out
varying vec4 myColor;

void main( ){
  vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
  vec4 diffuse = vec4(0.5, 0.5, 0.5, 1.0);
  vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);
  float shininess = 100;
  
	// Transforming The Vertex
  gl_Position = projectionMatrix * modelViewMatrix * gl_Vertex;

  // Calculating the color at this vertex
  // Fill me in!
  // The next two lines are place holders.
  vec4 color0 = vec4(0.0, 0.0, 0.0, 1.0);
  vec4 color1 = vec4(0.0, 0.0, 0.0, 1.0);
  
  // Sum the colors and pass it along to the fragment shader.
  myColor = ambient + color0 + color1;
}

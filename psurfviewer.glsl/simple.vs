void main( ){
	// Transforming The Vertex (ignores the normals, etc.)
	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	// Or apply the fixed function pipeline
	gl_Position = ftransform( );
}

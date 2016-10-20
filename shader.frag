// varying vec3 ec_vnormal, ec_vposition;

void main() {
//  vec3 P, N, L, V, H, light_position;
//  vec4 diffuse_color, specular_color;
//  float shininess = 1.0;
//  float pi = 3.14159;
//
//  light_position = vec3(5.0, 5.0, 5.0);
//
//  P = ec_vposition;
//  L = normalize(light_position - P);
//  V = normalize(-P);
//  H = normalize(L+V);
//  N = normalize(ec_vnormal - P);

//  diffuse_color = vec4(0.6, 0.3, 0.3, 1.0)*max(dot(N,L), 0.0);
//  specular_color = vec4(1.0, 1.0, 1.0, 1.0)*pow(max(dot(H,N), 0.0), shininess);
//  specular_color *= (shininess+2.0)/(8.0*pi);

//  gl_FragColor = 0.8 * (diffuse_color);
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}

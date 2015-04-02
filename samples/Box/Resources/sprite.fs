
uniform sampler2D   Texture;

varying   vec2      vVertexTexCoord;

void main(){
    gl_FragColor = texture2D(Texture, vVertexTexCoord);
}


uniform   mat4  Projection, View, Model;

attribute vec4  VertexPosition;

attribute vec2  VertexTexCoord;

varying   vec2  vVertexTexCoord;

void main(){
    gl_Position = Projection * View * Model * VertexPosition;
    vVertexTexCoord = VertexTexCoord;
}

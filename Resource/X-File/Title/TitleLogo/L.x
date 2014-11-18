xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 12;
 -10.78093;15.33376;-5.00000;,
 -4.06706;15.33376;-5.00000;,
 -4.06706;-10.24000;-5.00000;,
 -10.78093;-15.32627;-5.00000;,
 10.50000;-15.32627;-5.00000;,
 10.50000;-10.24000;-5.00000;,
 -4.06706;-10.24000;5.00000;,
 -4.06706;15.33376;5.00000;,
 -10.78093;15.33376;5.00000;,
 -10.78093;-15.32627;5.00000;,
 10.50000;-15.32627;5.00000;,
 10.50000;-10.24000;5.00000;;
 
 14;
 3;0,1,2;,
 3;3,0,2;,
 3;4,3,2;,
 3;5,4,2;,
 3;6,7,8;,
 3;6,8,9;,
 3;6,9,10;,
 3;6,10,11;,
 4;6,11,5,2;,
 4;7,6,2,1;,
 4;8,7,1,0;,
 4;9,8,0,3;,
 4;10,9,3,4;,
 4;11,10,4,5;;
 
 MeshMaterialList {
  1;
  14;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   50.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "LightGreen.png";
   }
  }
 }
 MeshNormals {
  8;
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;;
  14;
  3;0,1,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,3,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  12;
  0.000000;0.264159;,
  0.161133;0.264159;,
  0.161133;0.877930;,
  0.000000;1.000000;,
  0.510742;1.000000;,
  0.510742;0.877930;,
  0.161133;0.877930;,
  0.161133;0.264159;,
  0.000000;0.264159;,
  0.000000;1.000000;,
  0.510742;1.000000;,
  0.510742;0.877930;;
 }
}

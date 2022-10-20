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
 29;
 -18.29830;78.69750;1.60090;,
 -17.18079;78.69750;-6.49698;,
 -15.78412;-0.82373;-5.96882;,
 -16.81077;-0.82373;1.47076;,
 -12.66044;78.69750;-13.30805;,
 -11.63123;-0.82373;-12.22619;,
 -5.63250;78.69750;-17.48329;,
 -5.17463;-0.82373;-16.06203;,
 2.51100;78.69750;-18.19576;,
 2.30688;-0.82373;-16.71656;,
 10.15718;78.69750;-15.30433;,
 9.33147;-0.82373;-14.06018;,
 15.79161;78.69750;-9.38169;,
 14.50784;-0.82373;-8.61902;,
 18.29830;78.69750;-1.60090;,
 16.81077;-0.82373;-1.47074;,
 17.18079;78.69750;6.49698;,
 15.78412;-0.82373;5.96882;,
 12.66044;78.69750;13.30805;,
 11.63123;-0.82373;12.22619;,
 5.63250;78.69750;17.48329;,
 5.17462;-0.82373;16.06202;,
 -2.51102;78.69750;18.19576;,
 -2.30688;-0.82373;16.71656;,
 -10.15718;78.69750;15.30431;,
 -9.33149;-0.82373;14.06018;,
 -15.79161;78.69750;9.38167;,
 -14.50786;-0.82373;8.61901;,
 0.00000;74.91843;0.00000;;
 
 28;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,0,3,27;,
 3;28,1,0;,
 3;28,4,1;,
 3;28,6,4;,
 3;28,8,6;,
 3;28,10,8;,
 3;28,12,10;,
 3;28,14,12;,
 3;28,16,14;,
 3;28,18,16;,
 3;28,20,18;,
 3;28,22,20;,
 3;28,24,22;,
 3;28,26,24;,
 3;28,0,26;;
 
 MeshMaterialList {
  1;
  28;
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
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\redbull.png";
   }
  }
 }
 MeshNormals {
  29;
  0.000000;1.000000;-0.000000;,
  -0.996019;-0.018774;0.087140;,
  -0.935191;-0.018774;-0.353646;,
  -0.689137;-0.018774;-0.724387;,
  -0.306590;-0.018774;-0.951656;,
  0.136680;-0.018774;-0.990437;,
  0.552879;-0.018774;-0.833050;,
  0.859573;-0.018774;-0.510667;,
  0.996019;-0.018774;-0.087140;,
  0.935191;-0.018774;0.353646;,
  0.689137;-0.018774;0.724388;,
  0.306590;-0.018774;0.951656;,
  -0.136680;-0.018774;0.990437;,
  -0.552879;-0.018774;0.833050;,
  -0.859574;-0.018774;0.510667;,
  0.188492;0.979485;0.071279;,
  0.200753;0.979485;-0.017563;,
  0.138899;0.979485;0.146004;,
  0.061795;0.979485;0.191811;,
  -0.027548;0.979485;0.199628;,
  -0.111435;0.979485;0.167905;,
  -0.173251;0.979485;0.102927;,
  -0.200753;0.979485;0.017563;,
  -0.188492;0.979485;-0.071279;,
  -0.138899;0.979485;-0.146004;,
  -0.061795;0.979484;-0.191811;,
  0.027549;0.979484;-0.199627;,
  0.111436;0.979484;-0.167905;,
  0.173251;0.979485;-0.102928;;
  28;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,1,1,14;,
  3;0,15,16;,
  3;0,17,15;,
  3;0,18,17;,
  3;0,19,18;,
  3;0,20,19;,
  3;0,21,20;,
  3;0,22,21;,
  3;0,23,22;,
  3;0,24,23;,
  3;0,25,24;,
  3;0,26,25;,
  3;0,27,26;,
  3;0,28,27;,
  3;0,16,28;;
 }
 MeshTextureCoords {
  29;
  0.016263;0.000000;,
  0.000000;0.000000;,
  0.040646;1.000000;,
  0.055588;1.000000;,
  0.082767;0.000000;,
  0.116686;1.000000;,
  0.248173;0.000000;,
  0.268645;1.000000;,
  0.463456;0.000000;,
  0.466427;1.000000;,
  0.685978;0.000000;,
  0.670859;1.000000;,
  0.871664;0.000000;,
  0.841449;1.000000;,
  0.983737;0.000000;,
  0.944412;1.000000;,
  1.000000;0.000000;,
  0.959354;1.000000;,
  0.917233;0.000000;,
  0.883314;1.000000;,
  0.751827;0.000000;,
  0.731355;1.000000;,
  0.536543;0.000000;,
  0.533573;1.000000;,
  0.314022;0.000000;,
  0.329141;1.000000;,
  0.128336;0.000000;,
  0.158550;1.000000;,
  0.500000;0.047523;;
 }
}

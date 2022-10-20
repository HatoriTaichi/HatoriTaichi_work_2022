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
 80;
 0.07896;0.00017;-2.42599;,
 0.07896;-0.70619;-2.21417;,
 4.04418;-0.70619;-2.21417;,
 4.04418;0.00017;-2.42599;,
 0.07896;-1.29042;-1.61535;,
 4.04418;-1.29042;-1.61535;,
 0.07896;-1.65147;-0.73306;,
 4.04417;-1.65147;-0.73306;,
 0.07896;-1.72697;0.28013;,
 4.04418;-1.72697;0.28013;,
 0.07896;-1.50382;1.24905;,
 4.04418;-1.50382;1.24905;,
 0.07896;-1.02061;2.00615;,
 4.04418;-1.02061;2.00615;,
 0.07896;-0.36091;2.42052;,
 4.04418;-0.36091;2.42052;,
 0.07896;0.36124;2.42052;,
 4.04417;0.36124;2.42052;,
 0.07896;1.02095;2.00615;,
 4.04418;1.02095;2.00615;,
 0.07897;1.50415;1.24905;,
 4.04418;1.50414;1.24905;,
 0.07896;1.72730;0.28013;,
 4.04417;1.72730;0.28013;,
 0.07896;1.65183;-0.73306;,
 4.04418;1.65183;-0.73306;,
 0.07896;1.29074;-1.61535;,
 4.04418;1.29074;-1.61535;,
 0.07896;0.70652;-2.21417;,
 4.04418;0.70652;-2.21417;,
 0.07896;0.00017;-2.42599;,
 4.04418;0.00017;-2.42599;,
 6.53466;-0.70618;-2.21417;,
 6.53465;0.00017;-2.42599;,
 6.53464;-1.29041;-1.61535;,
 6.53464;-1.65147;-0.73306;,
 6.53465;-1.72697;0.28013;,
 6.53465;-1.50382;1.24905;,
 6.53465;-1.02061;2.00615;,
 6.53465;-0.36091;2.42052;,
 6.53465;0.36124;2.42052;,
 6.53465;1.02095;2.00615;,
 6.53465;1.50414;1.24905;,
 6.53464;1.72730;0.28013;,
 6.53465;1.65183;-0.73306;,
 6.53465;1.29074;-1.61535;,
 6.53464;0.70652;-2.21417;,
 6.53465;0.00017;-2.42599;,
 9.02517;-0.70619;-2.21417;,
 9.02517;0.00017;-2.42599;,
 9.02516;-1.29041;-1.61535;,
 9.02517;-1.65146;-0.73306;,
 9.02517;-1.72697;0.28013;,
 9.02517;-1.50382;1.24905;,
 9.02517;-1.02061;2.00615;,
 9.02517;-0.36091;2.42052;,
 9.02517;0.36124;2.42052;,
 9.02517;1.02095;2.00615;,
 9.02517;1.50414;1.24905;,
 9.02517;1.72729;0.28013;,
 9.02517;1.65183;-0.73306;,
 9.02517;1.29074;-1.61535;,
 9.02516;0.70652;-2.21417;,
 9.02517;0.00017;-2.42599;,
 11.51563;-0.70619;-2.21417;,
 11.51562;0.00017;-2.42599;,
 11.51563;-1.29042;-1.61535;,
 11.51563;-1.65147;-0.73306;,
 11.51562;-1.72696;0.28013;,
 11.51563;-1.50382;1.24905;,
 11.51563;-1.02061;2.00615;,
 11.51563;-0.36091;2.42052;,
 11.51563;0.36124;2.42052;,
 11.51563;1.02095;2.00615;,
 11.51563;1.50414;1.24905;,
 11.51562;1.72730;0.28013;,
 11.51563;1.65183;-0.73306;,
 11.51563;1.29074;-1.61535;,
 11.51562;0.70652;-2.21417;,
 11.51562;0.00017;-2.42599;;
 
 67;
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;5,7,6,4;,
 4;7,9,8,6;,
 4;9,11,10,8;,
 4;11,13,12,10;,
 4;13,15,14,12;,
 4;15,17,16,14;,
 4;17,19,18,16;,
 4;19,21,20,18;,
 4;21,23,22,20;,
 4;23,25,24,22;,
 4;25,27,26,24;,
 4;27,29,28,26;,
 4;29,31,30,28;,
 4;33,32,2,3;,
 4;32,34,5,2;,
 4;34,35,7,5;,
 4;35,36,9,7;,
 4;36,37,11,9;,
 4;37,38,13,11;,
 4;38,39,15,13;,
 4;39,40,17,15;,
 4;40,41,19,17;,
 4;41,42,21,19;,
 4;42,43,23,21;,
 4;43,44,25,23;,
 4;44,45,27,25;,
 4;45,46,29,27;,
 4;46,47,31,29;,
 4;49,48,32,33;,
 4;48,50,34,32;,
 4;50,51,35,34;,
 4;51,52,36,35;,
 4;52,53,37,36;,
 4;53,54,38,37;,
 4;54,55,39,38;,
 4;55,56,40,39;,
 4;56,57,41,40;,
 4;57,58,42,41;,
 4;58,59,43,42;,
 4;59,60,44,43;,
 4;60,61,45,44;,
 4;61,62,46,45;,
 4;62,63,47,46;,
 4;65,64,48,49;,
 4;64,66,50,48;,
 4;66,67,51,50;,
 4;67,68,52,51;,
 4;68,69,53,52;,
 4;69,70,54,53;,
 4;70,71,55,54;,
 4;71,72,56,55;,
 4;72,73,57,56;,
 4;73,74,58,57;,
 4;74,75,59,58;,
 4;75,76,60,59;,
 4;76,77,61,60;,
 4;77,78,62,61;,
 4;78,79,63,62;,
 4;22,8,14,16;,
 4;16,18,20,22;,
 4;8,10,12,14;,
 4;22,28,1,8;,
 3;0,1,28;,
 4;24,26,28,22;,
 4;6,8,1,4;;
 
 MeshMaterialList {
  3;
  67;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.458400;0.749600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  86;
  -0.000000;0.000001;-1.000000;,
  0.000000;-0.518023;-0.855367;,
  0.000000;-0.836052;-0.548650;,
  0.000000;-0.973345;-0.229346;,
  -0.000000;-0.997114;0.075918;,
  -0.000000;-0.922144;0.386847;,
  0.000000;-0.704548;0.709656;,
  0.000000;-0.276758;0.960940;,
  0.000000;0.276756;0.960940;,
  0.000001;0.704551;0.709654;,
  0.000001;0.922145;0.386844;,
  0.000001;0.997113;0.075934;,
  0.000000;0.973344;-0.229349;,
  -0.000000;0.836045;-0.548660;,
  -0.000000;0.518028;-0.855364;,
  0.000000;0.000000;-1.000000;,
  0.000001;-0.518024;-0.855366;,
  0.000001;-0.836052;-0.548650;,
  0.000000;-0.973345;-0.229347;,
  -0.000000;-0.997114;0.075918;,
  0.000000;-0.922144;0.386847;,
  -0.000000;-0.704548;0.709656;,
  -0.000000;-0.276758;0.960940;,
  -0.000000;0.276756;0.960940;,
  0.000000;0.704551;0.709653;,
  0.000000;0.922145;0.386844;,
  0.000000;0.997113;0.075934;,
  0.000000;0.973344;-0.229349;,
  0.000000;0.836045;-0.548660;,
  0.000000;0.518028;-0.855364;,
  0.000000;0.000001;-1.000000;,
  0.000000;-0.518025;-0.855366;,
  0.000001;-0.836052;-0.548650;,
  0.000001;-0.973344;-0.229349;,
  0.000000;-0.997114;0.075917;,
  0.000000;-0.922144;0.386847;,
  0.000000;-0.704548;0.709656;,
  -0.000000;-0.276758;0.960940;,
  -0.000000;0.276757;0.960940;,
  -0.000000;0.704552;0.709652;,
  0.000000;0.922145;0.386843;,
  0.000001;0.997113;0.075935;,
  0.000000;0.973344;-0.229349;,
  0.000000;0.836045;-0.548661;,
  0.000000;0.518028;-0.855364;,
  -0.000000;0.000002;-1.000000;,
  -0.000000;-0.518025;-0.855366;,
  -0.000001;-0.836053;-0.548649;,
  0.000000;-0.973345;-0.229348;,
  0.000001;-0.997114;0.075916;,
  0.000000;-0.922144;0.386847;,
  -0.000000;-0.704548;0.709656;,
  -0.000000;-0.276758;0.960940;,
  0.000000;0.276757;0.960940;,
  -0.000000;0.704553;0.709652;,
  -0.000000;0.922146;0.386843;,
  -0.000000;0.997113;0.075935;,
  -0.000000;0.973345;-0.229348;,
  -0.000000;0.836044;-0.548662;,
  -0.000000;0.518028;-0.855364;,
  -0.000000;0.000003;-1.000000;,
  -0.000000;-0.518024;-0.855366;,
  -0.000002;-0.836053;-0.548649;,
  -0.000001;-0.973345;-0.229346;,
  0.000001;-0.997114;0.075916;,
  0.000001;-0.922145;0.386846;,
  -0.000000;-0.704548;0.709656;,
  -0.000000;-0.276758;0.960940;,
  0.000000;0.276757;0.960940;,
  -0.000000;0.704553;0.709651;,
  -0.000001;0.922146;0.386843;,
  -0.000002;0.997113;0.075936;,
  -0.000001;0.973345;-0.229348;,
  0.000000;0.836044;-0.548662;,
  -0.000000;0.518028;-0.855364;,
  -1.000000;0.000015;0.000010;,
  -1.000000;-0.000001;0.000001;,
  -1.000000;0.000005;0.000002;,
  -1.000000;0.000012;0.000003;,
  -1.000000;0.000032;0.000017;,
  -1.000000;-0.000001;0.000000;,
  -1.000000;0.000005;-0.000003;,
  -1.000000;0.000004;-0.000008;,
  -1.000000;-0.000005;-0.000015;,
  -1.000000;0.000021;-0.000009;,
  -1.000000;0.000024;0.000005;;
  67;
  4;15,16,1,0;,
  4;16,17,2,1;,
  4;17,18,3,2;,
  4;18,19,4,3;,
  4;19,20,5,4;,
  4;20,21,6,5;,
  4;21,22,7,6;,
  4;22,23,8,7;,
  4;23,24,9,8;,
  4;24,25,10,9;,
  4;25,26,11,10;,
  4;26,27,12,11;,
  4;27,28,13,12;,
  4;28,29,14,13;,
  4;29,15,0,14;,
  4;30,31,16,15;,
  4;31,32,17,16;,
  4;32,33,18,17;,
  4;33,34,19,18;,
  4;34,35,20,19;,
  4;35,36,21,20;,
  4;36,37,22,21;,
  4;37,38,23,22;,
  4;38,39,24,23;,
  4;39,40,25,24;,
  4;40,41,26,25;,
  4;41,42,27,26;,
  4;42,43,28,27;,
  4;43,44,29,28;,
  4;44,30,15,29;,
  4;45,46,31,30;,
  4;46,47,32,31;,
  4;47,48,33,32;,
  4;48,49,34,33;,
  4;49,50,35,34;,
  4;50,51,36,35;,
  4;51,52,37,36;,
  4;52,53,38,37;,
  4;53,54,39,38;,
  4;54,55,40,39;,
  4;55,56,41,40;,
  4;56,57,42,41;,
  4;57,58,43,42;,
  4;58,59,44,43;,
  4;59,45,30,44;,
  4;60,61,46,45;,
  4;61,62,47,46;,
  4;62,63,48,47;,
  4;63,64,49,48;,
  4;64,65,50,49;,
  4;65,66,51,50;,
  4;66,67,52,51;,
  4;67,68,53,52;,
  4;68,69,54,53;,
  4;69,70,55,54;,
  4;70,71,56,55;,
  4;71,72,57,56;,
  4;72,73,58,57;,
  4;73,74,59,58;,
  4;74,60,45,59;,
  4;78,77,76,75;,
  4;75,79,79,78;,
  4;77,80,80,76;,
  4;78,82,81,77;,
  3;83,81,82;,
  4;84,84,82,78;,
  4;85,77,81,85;;
 }
 MeshTextureCoords {
  80;
  0.000000;0.000000;,
  0.066670;0.000000;,
  0.066670;0.200000;,
  0.000000;0.200000;,
  0.133330;0.000000;,
  0.133330;0.200000;,
  0.200000;0.000000;,
  0.200000;0.200000;,
  0.266670;0.000000;,
  0.266670;0.200000;,
  0.333330;0.000000;,
  0.333330;0.200000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.466670;0.000000;,
  0.466670;0.200000;,
  0.533330;0.000000;,
  0.533330;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.666670;0.000000;,
  0.666670;0.200000;,
  0.733330;0.000000;,
  0.733330;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  0.866670;0.000000;,
  0.866670;0.200000;,
  0.933330;0.000000;,
  0.933330;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.066670;0.400000;,
  0.000000;0.400000;,
  0.133330;0.400000;,
  0.200000;0.400000;,
  0.266670;0.400000;,
  0.333330;0.400000;,
  0.400000;0.400000;,
  0.466670;0.400000;,
  0.533330;0.400000;,
  0.600000;0.400000;,
  0.666670;0.400000;,
  0.733330;0.400000;,
  0.800000;0.400000;,
  0.866670;0.400000;,
  0.933330;0.400000;,
  1.000000;0.400000;,
  0.066670;0.600000;,
  0.000000;0.600000;,
  0.133330;0.600000;,
  0.200000;0.600000;,
  0.266670;0.600000;,
  0.333330;0.600000;,
  0.400000;0.600000;,
  0.466670;0.600000;,
  0.533330;0.600000;,
  0.600000;0.600000;,
  0.666670;0.600000;,
  0.733330;0.600000;,
  0.800000;0.600000;,
  0.866670;0.600000;,
  0.933330;0.600000;,
  1.000000;0.600000;,
  0.066670;0.800000;,
  0.000000;0.800000;,
  0.133330;0.800000;,
  0.200000;0.800000;,
  0.266670;0.800000;,
  0.333330;0.800000;,
  0.400000;0.800000;,
  0.466670;0.800000;,
  0.533330;0.800000;,
  0.600000;0.800000;,
  0.666670;0.800000;,
  0.733330;0.800000;,
  0.800000;0.800000;,
  0.866670;0.800000;,
  0.933330;0.800000;,
  1.000000;0.800000;;
 }
}

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
 214;
 0.01116;2.28787;-0.03763;,
 0.06973;2.51616;-0.62691;,
 0.06973;2.28787;-0.66959;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.71362;-0.50465;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.85358;-0.31932;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.91713;-0.09594;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.89570;0.13531;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.79218;0.34321;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.62055;0.49967;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.40400;0.58357;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.17175;0.58357;,
 0.01116;2.28787;-0.03763;,
 0.06973;1.95519;0.49967;,
 0.01116;2.28787;-0.03763;,
 0.06974;1.78356;0.34321;,
 0.01116;2.28787;-0.03763;,
 0.06973;1.68005;0.13531;,
 0.01116;2.28787;-0.03763;,
 0.06973;1.65861;-0.09594;,
 0.01116;2.28787;-0.03763;,
 0.06973;1.72216;-0.31932;,
 0.01116;2.28787;-0.03763;,
 0.06973;1.86213;-0.50465;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.05958;-0.62691;,
 0.01116;2.28787;-0.03763;,
 0.06973;2.28787;-0.66959;,
 0.24342;2.73667;-1.19613;,
 0.24342;2.28787;-1.28003;,
 0.24342;3.12486;-0.95577;,
 0.24341;3.40002;-0.59141;,
 0.24342;3.52496;-0.15226;,
 0.24342;3.48284;0.30237;,
 0.24342;3.27932;0.71108;,
 0.24341;2.94190;1.01868;,
 0.24341;2.51616;1.18361;,
 0.24342;2.05958;1.18361;,
 0.24342;1.63383;1.01868;,
 0.24342;1.29642;0.71108;,
 0.24342;1.09290;0.30237;,
 0.24341;1.05077;-0.15226;,
 0.24341;1.17573;-0.59141;,
 0.24342;1.45087;-0.95577;,
 0.24341;1.83907;-1.19613;,
 0.24342;2.28787;-1.28003;,
 0.52630;2.94190;-1.72589;,
 0.52630;2.28787;-1.84816;,
 0.52630;3.50761;-1.37562;,
 0.52630;3.90859;-0.84465;,
 0.52630;4.09067;-0.20468;,
 0.52630;4.02928;0.45784;,
 0.52630;3.73270;1.05346;,
 0.52630;3.24099;1.50171;,
 0.52630;2.62055;1.74207;,
 0.52630;1.95519;1.74207;,
 0.52630;1.33476;1.50171;,
 0.52630;0.84304;1.05346;,
 0.52630;0.54647;0.45784;,
 0.52630;0.48507;-0.20468;,
 0.52630;0.66716;-0.84465;,
 0.52630;1.06813;-1.37563;,
 0.52630;1.63384;-1.72590;,
 0.52630;2.28787;-1.84816;,
 0.90877;3.12486;-2.19817;,
 0.90877;2.28787;-2.35463;,
 0.90877;3.84882;-1.74991;,
 0.90877;4.36196;-1.07040;,
 0.90877;4.59499;-0.25141;,
 0.90877;4.51642;0.59645;,
 0.90877;4.13687;1.35868;,
 0.90877;3.50761;1.93232;,
 0.90877;2.71362;2.23992;,
 0.90877;1.86213;2.23992;,
 0.90877;1.06813;1.93232;,
 0.90877;0.43887;1.35868;,
 0.90877;0.05933;0.59645;,
 0.90877;-0.01924;-0.25142;,
 0.90877;0.21379;-1.07041;,
 0.90877;0.72692;-1.74991;,
 0.90877;1.45087;-2.19817;,
 0.90877;2.28787;-2.35463;,
 0.90877;2.28787;-2.35463;,
 0.90877;3.12486;-2.19817;,
 13.78044;3.12486;-2.19817;,
 13.78044;2.28787;-2.35463;,
 0.90877;3.84882;-1.74991;,
 13.78044;3.84882;-1.74991;,
 0.90877;4.36196;-1.07040;,
 13.78044;4.36196;-1.07040;,
 0.90877;4.59499;-0.25141;,
 13.78044;4.59498;-0.25141;,
 0.90877;4.51642;0.59645;,
 13.78044;4.51642;0.59645;,
 0.90877;4.13687;1.35868;,
 13.78044;4.13687;1.35868;,
 0.90877;3.50761;1.93232;,
 13.78044;3.50761;1.93232;,
 0.90877;2.71362;2.23992;,
 13.78044;2.71362;2.23992;,
 0.90877;1.86213;2.23992;,
 13.78044;1.86213;2.23992;,
 0.90877;1.06813;1.93232;,
 13.78044;1.06813;1.93232;,
 0.90877;0.43887;1.35868;,
 13.78044;0.43887;1.35868;,
 0.90877;0.05933;0.59645;,
 13.78044;0.05933;0.59645;,
 0.90877;-0.01924;-0.25142;,
 13.78044;-0.01924;-0.25142;,
 0.90877;0.21379;-1.07041;,
 13.78044;0.21379;-1.07041;,
 0.90877;0.72692;-1.74991;,
 13.78044;0.72692;-1.74991;,
 0.90877;1.45087;-2.19817;,
 13.78044;1.45087;-2.19817;,
 0.90877;2.28787;-2.35463;,
 13.78044;2.28787;-2.35463;,
 13.78044;2.28787;-2.35463;,
 13.78044;3.12486;-2.19817;,
 14.16291;2.94190;-1.72589;,
 14.16291;2.28787;-1.84815;,
 13.78044;3.84882;-1.74991;,
 14.16291;3.50761;-1.37562;,
 13.78044;4.36196;-1.07040;,
 14.16291;3.90859;-0.84465;,
 13.78044;4.59498;-0.25141;,
 14.16291;4.09067;-0.20468;,
 13.78044;4.51642;0.59645;,
 14.16291;4.02928;0.45784;,
 13.78044;4.13687;1.35868;,
 14.16291;3.73270;1.05346;,
 13.78044;3.50761;1.93232;,
 14.16291;3.24099;1.50171;,
 13.78044;2.71362;2.23992;,
 14.16291;2.62055;1.74207;,
 13.78044;1.86213;2.23992;,
 14.16291;1.95519;1.74207;,
 13.78044;1.06813;1.93232;,
 14.16291;1.33476;1.50171;,
 13.78044;0.43887;1.35868;,
 14.16291;0.84304;1.05346;,
 13.78044;0.05933;0.59645;,
 14.16291;0.54647;0.45784;,
 13.78044;-0.01924;-0.25142;,
 14.16291;0.48507;-0.20468;,
 13.78044;0.21379;-1.07041;,
 14.16292;0.66716;-0.84465;,
 13.78044;0.72692;-1.74991;,
 14.16291;1.06813;-1.37562;,
 13.78044;1.45087;-2.19817;,
 14.16291;1.63384;-1.72589;,
 13.78044;2.28787;-2.35463;,
 14.16291;2.28787;-1.84815;,
 14.44580;2.73667;-1.19613;,
 14.44580;2.28787;-1.28002;,
 14.44580;3.12486;-0.95577;,
 14.44580;3.40002;-0.59141;,
 14.44580;3.52496;-0.15226;,
 14.44580;3.48284;0.30237;,
 14.44580;3.27932;0.71108;,
 14.44580;2.94190;1.01868;,
 14.44580;2.51616;1.18361;,
 14.44580;2.05958;1.18361;,
 14.44580;1.63383;1.01868;,
 14.44580;1.29642;0.71108;,
 14.44580;1.09290;0.30237;,
 14.44580;1.05077;-0.15226;,
 14.44580;1.17573;-0.59141;,
 14.44580;1.45087;-0.95577;,
 14.44580;1.83907;-1.19613;,
 14.44580;2.28787;-1.28002;,
 14.61949;2.51616;-0.62691;,
 14.61949;2.28787;-0.66959;,
 14.61949;2.71362;-0.50465;,
 14.61949;2.85357;-0.31932;,
 14.61949;2.91713;-0.09594;,
 14.61949;2.89570;0.13531;,
 14.61949;2.79218;0.34321;,
 14.61949;2.62055;0.49967;,
 14.61949;2.40400;0.58357;,
 14.61949;2.17175;0.58357;,
 14.61949;1.95519;0.49967;,
 14.61949;1.78356;0.34321;,
 14.61949;1.68005;0.13531;,
 14.61949;1.65861;-0.09594;,
 14.61949;1.72216;-0.31932;,
 14.61949;1.86213;-0.50465;,
 14.61949;2.05958;-0.62691;,
 14.61949;2.28787;-0.66959;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;,
 14.67805;2.28787;-0.03763;;
 
 153;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,20;,
 3;23,24,22;,
 3;25,26,24;,
 3;27,28,26;,
 3;29,30,28;,
 3;31,32,30;,
 3;33,34,32;,
 4;2,1,35,36;,
 4;1,4,37,35;,
 4;4,6,38,37;,
 4;6,8,39,38;,
 4;8,10,40,39;,
 4;10,12,41,40;,
 4;12,14,42,41;,
 4;14,16,43,42;,
 4;16,18,44,43;,
 4;18,20,45,44;,
 4;20,22,46,45;,
 4;22,24,47,46;,
 4;24,26,48,47;,
 4;26,28,49,48;,
 4;28,30,50,49;,
 4;30,32,51,50;,
 4;32,34,52,51;,
 4;36,35,53,54;,
 4;35,37,55,53;,
 4;37,38,56,55;,
 4;38,39,57,56;,
 4;39,40,58,57;,
 4;40,41,59,58;,
 4;41,42,60,59;,
 4;42,43,61,60;,
 4;43,44,62,61;,
 4;44,45,63,62;,
 4;45,46,64,63;,
 4;46,47,65,64;,
 4;47,48,66,65;,
 4;48,49,67,66;,
 4;49,50,68,67;,
 4;50,51,69,68;,
 4;51,52,70,69;,
 4;54,53,71,72;,
 4;53,55,73,71;,
 4;55,56,74,73;,
 4;56,57,75,74;,
 4;57,58,76,75;,
 4;58,59,77,76;,
 4;59,60,78,77;,
 4;60,61,79,78;,
 4;61,62,80,79;,
 4;62,63,81,80;,
 4;63,64,82,81;,
 4;64,65,83,82;,
 4;65,66,84,83;,
 4;66,67,85,84;,
 4;67,68,86,85;,
 4;68,69,87,86;,
 4;69,70,88,87;,
 4;89,90,91,92;,
 4;90,93,94,91;,
 4;93,95,96,94;,
 4;95,97,98,96;,
 4;97,99,100,98;,
 4;99,101,102,100;,
 4;101,103,104,102;,
 4;103,105,106,104;,
 4;105,107,108,106;,
 4;107,109,110,108;,
 4;109,111,112,110;,
 4;111,113,114,112;,
 4;113,115,116,114;,
 4;115,117,118,116;,
 4;117,119,120,118;,
 4;119,121,122,120;,
 4;121,123,124,122;,
 4;125,126,127,128;,
 4;126,129,130,127;,
 4;129,131,132,130;,
 4;131,133,134,132;,
 4;133,135,136,134;,
 4;135,137,138,136;,
 4;137,139,140,138;,
 4;139,141,142,140;,
 4;141,143,144,142;,
 4;143,145,146,144;,
 4;145,147,148,146;,
 4;147,149,150,148;,
 4;149,151,152,150;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;155,157,158,156;,
 4;157,159,160,158;,
 4;128,127,161,162;,
 4;127,130,163,161;,
 4;130,132,164,163;,
 4;132,134,165,164;,
 4;134,136,166,165;,
 4;136,138,167,166;,
 4;138,140,168,167;,
 4;140,142,169,168;,
 4;142,144,170,169;,
 4;144,146,171,170;,
 4;146,148,172,171;,
 4;148,150,173,172;,
 4;150,152,174,173;,
 4;152,154,175,174;,
 4;154,156,176,175;,
 4;156,158,177,176;,
 4;158,160,178,177;,
 4;162,161,179,180;,
 4;161,163,181,179;,
 4;163,164,182,181;,
 4;164,165,183,182;,
 4;165,166,184,183;,
 4;166,167,185,184;,
 4;167,168,186,185;,
 4;168,169,187,186;,
 4;169,170,188,187;,
 4;170,171,189,188;,
 4;171,172,190,189;,
 4;172,173,191,190;,
 4;173,174,192,191;,
 4;174,175,193,192;,
 4;175,176,194,193;,
 4;176,177,195,194;,
 4;177,178,196,195;,
 3;180,179,197;,
 3;179,181,198;,
 3;181,182,199;,
 3;182,183,200;,
 3;183,184,201;,
 3;184,185,202;,
 3;185,186,203;,
 3;186,187,204;,
 3;187,188,205;,
 3;188,189,206;,
 3;189,190,207;,
 3;190,191,208;,
 3;191,192,209;,
 3;192,193,210;,
 3;193,194,211;,
 3;194,195,212;,
 3;195,196,213;;
 
 MeshMaterialList {
  1;
  153;
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
   0.800000;0.047200;0.499200;1.000000;;
   10.000000;
   0.000000;0.000000;0.000000;;
   0.350000;0.020650;0.218400;;
  }
 }
 MeshNormals {
  138;
  -1.000000;-0.000000;0.000000;,
  -0.982982;-0.000001;-0.183702;,
  -0.982982;0.066362;-0.171297;,
  -0.982982;0.123760;-0.135759;,
  -0.982982;0.164444;-0.081883;,
  -0.982982;0.182920;-0.016948;,
  -0.982982;0.176690;0.050272;,
  -0.982982;0.146598;0.110705;,
  -0.982982;0.096708;0.156186;,
  -0.982982;0.033758;0.180574;,
  -0.982982;-0.033755;0.180575;,
  -0.982982;-0.096710;0.156185;,
  -0.982982;-0.146600;0.110703;,
  -0.982982;-0.176689;0.050276;,
  -0.982982;-0.182918;-0.016946;,
  -0.982982;-0.164443;-0.081886;,
  -0.982982;-0.123759;-0.135760;,
  -0.982982;-0.066363;-0.171296;,
  -0.932511;0.000001;-0.361141;,
  -0.932510;0.130462;-0.336755;,
  -0.932510;0.243299;-0.266890;,
  -0.932511;0.323280;-0.160974;,
  -0.932511;0.359602;-0.033320;,
  -0.932511;0.347355;0.098830;,
  -0.932511;0.288196;0.217636;,
  -0.932511;0.190117;0.307047;,
  -0.932511;0.066360;0.354992;,
  -0.932511;-0.066360;0.354993;,
  -0.932511;-0.190118;0.307049;,
  -0.932511;-0.288199;0.217635;,
  -0.932510;-0.347356;0.098834;,
  -0.932511;-0.359601;-0.033320;,
  -0.932510;-0.323281;-0.160977;,
  -0.932511;-0.243300;-0.266886;,
  -0.932512;-0.130460;-0.336753;,
  -0.850289;0.000002;-0.526316;,
  -0.850289;0.190130;-0.490774;,
  -0.850289;0.354575;-0.388954;,
  -0.850289;0.471138;-0.234600;,
  -0.850290;0.524070;-0.048561;,
  -0.850290;0.506223;0.144033;,
  -0.850289;0.420009;0.317177;,
  -0.850289;0.277070;0.447484;,
  -0.850289;0.096711;0.517354;,
  -0.850289;-0.096711;0.517355;,
  -0.850288;-0.277069;0.447485;,
  -0.850288;-0.420010;0.317176;,
  -0.850287;-0.506227;0.144034;,
  -0.850287;-0.524073;-0.048563;,
  -0.850287;-0.471141;-0.234600;,
  -0.850289;-0.354579;-0.388950;,
  -0.850289;-0.190128;-0.490775;,
  -0.448159;0.000002;-0.893954;,
  -0.448160;0.322935;-0.833586;,
  -0.448159;0.602253;-0.660639;,
  -0.448159;0.800235;-0.398470;,
  -0.448160;0.890140;-0.082484;,
  -0.448160;0.859827;0.244643;,
  -0.448159;0.713389;0.538731;,
  -0.448158;0.470607;0.760055;,
  -0.448159;0.164266;0.878732;,
  -0.448159;-0.164265;0.878732;,
  -0.448159;-0.470605;0.760056;,
  -0.448160;-0.713391;0.538727;,
  -0.448158;-0.859829;0.244641;,
  -0.448158;-0.890141;-0.082485;,
  -0.448157;-0.800235;-0.398471;,
  -0.448158;-0.602257;-0.660636;,
  -0.448159;-0.322935;-0.833587;,
  0.448163;0.000001;-0.893952;,
  0.448162;0.322934;-0.833585;,
  0.448160;0.602253;-0.660639;,
  0.448158;0.800235;-0.398470;,
  0.448158;0.890141;-0.082484;,
  0.448159;0.859827;0.244642;,
  0.448159;0.713389;0.538731;,
  0.448158;0.470606;0.760055;,
  0.448160;0.164266;0.878732;,
  0.448159;-0.164265;0.878732;,
  0.448159;-0.470605;0.760056;,
  0.448161;-0.713390;0.538727;,
  0.448160;-0.859828;0.244640;,
  0.448159;-0.890140;-0.082485;,
  0.448158;-0.800235;-0.398471;,
  0.448160;-0.602256;-0.660636;,
  0.448163;-0.322935;-0.833585;,
  0.850290;-0.000000;-0.526315;,
  0.850289;0.190127;-0.490774;,
  0.850288;0.354576;-0.388955;,
  0.850288;0.471140;-0.234600;,
  0.850288;0.524073;-0.048562;,
  0.850288;0.506226;0.144032;,
  0.850288;0.420009;0.317178;,
  0.850288;0.277069;0.447484;,
  0.850289;0.096711;0.517355;,
  0.850288;-0.096710;0.517356;,
  0.850288;-0.277070;0.447485;,
  0.850288;-0.420011;0.317176;,
  0.850287;-0.506227;0.144034;,
  0.850287;-0.524073;-0.048562;,
  0.850287;-0.471141;-0.234600;,
  0.850288;-0.354578;-0.388953;,
  0.850289;-0.190127;-0.490775;,
  0.932508;-0.000000;-0.361151;,
  0.932508;0.130463;-0.336762;,
  0.932508;0.243304;-0.266894;,
  0.932508;0.323287;-0.160977;,
  0.932508;0.359609;-0.033322;,
  0.932508;0.347362;0.098832;,
  0.932508;0.288202;0.217641;,
  0.932508;0.190120;0.307055;,
  0.932508;0.066362;0.355000;,
  0.932508;-0.066360;0.355000;,
  0.932508;-0.190121;0.307055;,
  0.932508;-0.288205;0.217640;,
  0.932507;-0.347364;0.098834;,
  0.932508;-0.359610;-0.033320;,
  0.932508;-0.323288;-0.160979;,
  0.932507;-0.243305;-0.266894;,
  0.932507;-0.130462;-0.336764;,
  0.982982;-0.000000;-0.183700;,
  0.982982;0.066361;-0.171295;,
  0.982982;0.123758;-0.135756;,
  0.982982;0.164442;-0.081882;,
  0.982982;0.182916;-0.016950;,
  0.982982;0.176687;0.050271;,
  0.982982;0.146595;0.110704;,
  0.982982;0.096707;0.156185;,
  0.982982;0.033756;0.180572;,
  0.982982;-0.033755;0.180572;,
  0.982983;-0.096706;0.156184;,
  0.982983;-0.146596;0.110701;,
  0.982982;-0.176687;0.050272;,
  0.982982;-0.182916;-0.016946;,
  0.982982;-0.164441;-0.081883;,
  0.982982;-0.123757;-0.135758;,
  0.982982;-0.066362;-0.171295;,
  1.000000;0.000000;-0.000000;;
  153;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,17,16;,
  3;0,1,17;,
  4;1,2,19,18;,
  4;2,3,20,19;,
  4;3,4,21,20;,
  4;4,5,22,21;,
  4;5,6,23,22;,
  4;6,7,24,23;,
  4;7,8,25,24;,
  4;8,9,26,25;,
  4;9,10,27,26;,
  4;10,11,28,27;,
  4;11,12,29,28;,
  4;12,13,30,29;,
  4;13,14,31,30;,
  4;14,15,32,31;,
  4;15,16,33,32;,
  4;16,17,34,33;,
  4;17,1,18,34;,
  4;18,19,36,35;,
  4;19,20,37,36;,
  4;20,21,38,37;,
  4;21,22,39,38;,
  4;22,23,40,39;,
  4;23,24,41,40;,
  4;24,25,42,41;,
  4;25,26,43,42;,
  4;26,27,44,43;,
  4;27,28,45,44;,
  4;28,29,46,45;,
  4;29,30,47,46;,
  4;30,31,48,47;,
  4;31,32,49,48;,
  4;32,33,50,49;,
  4;33,34,51,50;,
  4;34,18,35,51;,
  4;35,36,53,52;,
  4;36,37,54,53;,
  4;37,38,55,54;,
  4;38,39,56,55;,
  4;39,40,57,56;,
  4;40,41,58,57;,
  4;41,42,59,58;,
  4;42,43,60,59;,
  4;43,44,61,60;,
  4;44,45,62,61;,
  4;45,46,63,62;,
  4;46,47,64,63;,
  4;47,48,65,64;,
  4;48,49,66,65;,
  4;49,50,67,66;,
  4;50,51,68,67;,
  4;51,35,52,68;,
  4;52,53,70,69;,
  4;53,54,71,70;,
  4;54,55,72,71;,
  4;55,56,73,72;,
  4;56,57,74,73;,
  4;57,58,75,74;,
  4;58,59,76,75;,
  4;59,60,77,76;,
  4;60,61,78,77;,
  4;61,62,79,78;,
  4;62,63,80,79;,
  4;63,64,81,80;,
  4;64,65,82,81;,
  4;65,66,83,82;,
  4;66,67,84,83;,
  4;67,68,85,84;,
  4;68,52,69,85;,
  4;69,70,87,86;,
  4;70,71,88,87;,
  4;71,72,89,88;,
  4;72,73,90,89;,
  4;73,74,91,90;,
  4;74,75,92,91;,
  4;75,76,93,92;,
  4;76,77,94,93;,
  4;77,78,95,94;,
  4;78,79,96,95;,
  4;79,80,97,96;,
  4;80,81,98,97;,
  4;81,82,99,98;,
  4;82,83,100,99;,
  4;83,84,101,100;,
  4;84,85,102,101;,
  4;85,69,86,102;,
  4;86,87,104,103;,
  4;87,88,105,104;,
  4;88,89,106,105;,
  4;89,90,107,106;,
  4;90,91,108,107;,
  4;91,92,109,108;,
  4;92,93,110,109;,
  4;93,94,111,110;,
  4;94,95,112,111;,
  4;95,96,113,112;,
  4;96,97,114,113;,
  4;97,98,115,114;,
  4;98,99,116,115;,
  4;99,100,117,116;,
  4;100,101,118,117;,
  4;101,102,119,118;,
  4;102,86,103,119;,
  4;103,104,121,120;,
  4;104,105,122,121;,
  4;105,106,123,122;,
  4;106,107,124,123;,
  4;107,108,125,124;,
  4;108,109,126,125;,
  4;109,110,127,126;,
  4;110,111,128,127;,
  4;111,112,129,128;,
  4;112,113,130,129;,
  4;113,114,131,130;,
  4;114,115,132,131;,
  4;115,116,133,132;,
  4;116,117,134,133;,
  4;117,118,135,134;,
  4;118,119,136,135;,
  4;119,103,120,136;,
  3;120,121,137;,
  3;121,122,137;,
  3;122,123,137;,
  3;123,124,137;,
  3;124,125,137;,
  3;125,126,137;,
  3;126,127,137;,
  3;127,128,137;,
  3;128,129,137;,
  3;129,130,137;,
  3;130,131,137;,
  3;131,132,137;,
  3;132,133,137;,
  3;133,134,137;,
  3;134,135,137;,
  3;135,136,137;,
  3;136,120,137;;
 }
 MeshTextureCoords {
  214;
  0.029410;0.000000;,
  0.058820;0.058820;,
  0.000000;0.058820;,
  0.088240;0.000000;,
  0.117650;0.058820;,
  0.147060;0.000000;,
  0.176470;0.058820;,
  0.205880;0.000000;,
  0.235290;0.058820;,
  0.264710;0.000000;,
  0.294120;0.058820;,
  0.323530;0.000000;,
  0.352940;0.058820;,
  0.382350;0.000000;,
  0.411760;0.058820;,
  0.441180;0.000000;,
  0.470590;0.058820;,
  0.500000;0.000000;,
  0.529410;0.058820;,
  0.558820;0.000000;,
  0.588240;0.058820;,
  0.617650;0.000000;,
  0.647060;0.058820;,
  0.676470;0.000000;,
  0.705880;0.058820;,
  0.735290;0.000000;,
  0.764710;0.058820;,
  0.794120;0.000000;,
  0.823530;0.058820;,
  0.852940;0.000000;,
  0.882350;0.058820;,
  0.911760;0.000000;,
  0.941180;0.058820;,
  0.970590;0.000000;,
  1.000000;0.058820;,
  0.058820;0.117650;,
  0.000000;0.117650;,
  0.117650;0.117650;,
  0.176470;0.117650;,
  0.235290;0.117650;,
  0.294120;0.117650;,
  0.352940;0.117650;,
  0.411760;0.117650;,
  0.470590;0.117650;,
  0.529410;0.117650;,
  0.588240;0.117650;,
  0.647060;0.117650;,
  0.705880;0.117650;,
  0.764710;0.117650;,
  0.823530;0.117650;,
  0.882350;0.117650;,
  0.941180;0.117650;,
  1.000000;0.117650;,
  0.058820;0.176470;,
  0.000000;0.176470;,
  0.117650;0.176470;,
  0.176470;0.176470;,
  0.235290;0.176470;,
  0.294120;0.176470;,
  0.352940;0.176470;,
  0.411760;0.176470;,
  0.470590;0.176470;,
  0.529410;0.176470;,
  0.588240;0.176470;,
  0.647060;0.176470;,
  0.705880;0.176470;,
  0.764710;0.176470;,
  0.823530;0.176470;,
  0.882350;0.176470;,
  0.941180;0.176470;,
  1.000000;0.176470;,
  0.058820;0.235290;,
  0.000000;0.235290;,
  0.117650;0.235290;,
  0.176470;0.235290;,
  0.235290;0.235290;,
  0.294120;0.235290;,
  0.352940;0.235290;,
  0.411760;0.235290;,
  0.470590;0.235290;,
  0.529410;0.235290;,
  0.588240;0.235290;,
  0.647060;0.235290;,
  0.705880;0.235290;,
  0.764710;0.235290;,
  0.823530;0.235290;,
  0.882350;0.235290;,
  0.941180;0.235290;,
  1.000000;0.235290;,
  0.000000;0.470590;,
  0.058820;0.470590;,
  0.058820;0.529410;,
  0.000000;0.529410;,
  0.117650;0.470590;,
  0.117650;0.529410;,
  0.176470;0.470590;,
  0.176470;0.529410;,
  0.235290;0.470590;,
  0.235290;0.529410;,
  0.294120;0.470590;,
  0.294120;0.529410;,
  0.352940;0.470590;,
  0.352940;0.529410;,
  0.411760;0.470590;,
  0.411760;0.529410;,
  0.470590;0.470590;,
  0.470590;0.529410;,
  0.529410;0.470590;,
  0.529410;0.529410;,
  0.588240;0.470590;,
  0.588240;0.529410;,
  0.647060;0.470590;,
  0.647060;0.529410;,
  0.705880;0.470590;,
  0.705880;0.529410;,
  0.764710;0.470590;,
  0.764710;0.529410;,
  0.823530;0.470590;,
  0.823530;0.529410;,
  0.882350;0.470590;,
  0.882350;0.529410;,
  0.941180;0.470590;,
  0.941180;0.529410;,
  1.000000;0.470590;,
  1.000000;0.529410;,
  0.000000;0.764710;,
  0.058820;0.764710;,
  0.058820;0.823530;,
  0.000000;0.823530;,
  0.117650;0.764710;,
  0.117650;0.823530;,
  0.176470;0.764710;,
  0.176470;0.823530;,
  0.235290;0.764710;,
  0.235290;0.823530;,
  0.294120;0.764710;,
  0.294120;0.823530;,
  0.352940;0.764710;,
  0.352940;0.823530;,
  0.411760;0.764710;,
  0.411760;0.823530;,
  0.470590;0.764710;,
  0.470590;0.823530;,
  0.529410;0.764710;,
  0.529410;0.823530;,
  0.588240;0.764710;,
  0.588240;0.823530;,
  0.647060;0.764710;,
  0.647060;0.823530;,
  0.705880;0.764710;,
  0.705880;0.823530;,
  0.764710;0.764710;,
  0.764710;0.823530;,
  0.823530;0.764710;,
  0.823530;0.823530;,
  0.882350;0.764710;,
  0.882350;0.823530;,
  0.941180;0.764710;,
  0.941180;0.823530;,
  1.000000;0.764710;,
  1.000000;0.823530;,
  0.058820;0.882350;,
  0.000000;0.882350;,
  0.117650;0.882350;,
  0.176470;0.882350;,
  0.235290;0.882350;,
  0.294120;0.882350;,
  0.352940;0.882350;,
  0.411760;0.882350;,
  0.470590;0.882350;,
  0.529410;0.882350;,
  0.588240;0.882350;,
  0.647060;0.882350;,
  0.705880;0.882350;,
  0.764710;0.882350;,
  0.823530;0.882350;,
  0.882350;0.882350;,
  0.941180;0.882350;,
  1.000000;0.882350;,
  0.058820;0.941180;,
  0.000000;0.941180;,
  0.117650;0.941180;,
  0.176470;0.941180;,
  0.235290;0.941180;,
  0.294120;0.941180;,
  0.352940;0.941180;,
  0.411760;0.941180;,
  0.470590;0.941180;,
  0.529410;0.941180;,
  0.588240;0.941180;,
  0.647060;0.941180;,
  0.705880;0.941180;,
  0.764710;0.941180;,
  0.823530;0.941180;,
  0.882350;0.941180;,
  0.941180;0.941180;,
  1.000000;0.941180;,
  0.029410;1.000000;,
  0.088240;1.000000;,
  0.147060;1.000000;,
  0.205880;1.000000;,
  0.264710;1.000000;,
  0.323530;1.000000;,
  0.382350;1.000000;,
  0.441180;1.000000;,
  0.500000;1.000000;,
  0.558820;1.000000;,
  0.617650;1.000000;,
  0.676470;1.000000;,
  0.735290;1.000000;,
  0.794120;1.000000;,
  0.852940;1.000000;,
  0.911760;1.000000;,
  0.970590;1.000000;;
 }
}

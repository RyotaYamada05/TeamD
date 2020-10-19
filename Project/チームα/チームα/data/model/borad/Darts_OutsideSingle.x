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
 160;
 -450.01389;-35.46965;0.00000;,
 -445.84921;-70.66827;-0.00001;,
 -311.31750;-49.36089;0.00001;,
 -314.22610;-24.78303;0.00000;,
 -438.93460;-105.43164;-0.00000;,
 -306.48871;-73.63448;0.00000;,
 -429.31299;-139.54510;0.00002;,
 -299.77130;-97.45460;0.00000;,
 -417.04401;-172.79871;0.00002;,
 -291.20459;-120.67418;0.00003;,
 -402.20551;-204.98712;0.00002;,
 -280.84311;-143.14986;0.00003;,
 -384.88708;-235.91231;0.00003;,
 -268.75031;-164.74388;0.00003;,
 -365.19510;-265.38339;-0.00001;,
 -255.00101;-185.32196;0.00001;,
 -343.25159;-293.21832;-0.00001;,
 -239.67850;-204.75748;-0.00001;,
 -319.19199;-319.24615;0.00008;,
 -222.87880;-222.93233;0.00003;,
 -293.16519;-343.30505;0.00006;,
 -204.70441;-239.73206;0.00000;,
 -265.33020;-365.24896;0.00006;,
 -185.26880;-255.05417;0.00005;,
 -235.85941;-384.94034;0.00012;,
 -164.69040;-268.80338;0.00001;,
 -204.93401;-402.25864;-0.00001;,
 -143.09680;-280.89688;-0.00004;,
 -172.74550;-417.09918;0.00000;,
 -120.62070;-291.25873;0.00007;,
 -139.49181;-429.36676;0.00002;,
 -97.40130;-299.82495;0.00003;,
 -105.37820;-438.98859;0.00000;,
 -73.58120;-306.54337;0.00002;,
 -70.61530;-445.90271;0.00006;,
 -49.30760;-311.37073;0.00006;,
 -35.41670;-450.06778;0.00004;,
 -24.73000;-314.28027;0.00001;,
 0.00030;-451.45984;-0.00004;,
 0.00030;-315.25235;0.00002;,
 35.41720;-450.06778;0.00004;,
 24.73040;-314.28027;0.00001;,
 70.61560;-445.90308;-0.00000;,
 49.30820;-311.37082;0.00004;,
 105.37920;-438.98859;0.00000;,
 73.58190;-306.54337;0.00002;,
 139.49249;-429.36694;0.00003;,
 97.40190;-299.82510;0.00002;,
 172.74600;-417.09918;0.00000;,
 120.62160;-291.25885;0.00002;,
 204.93440;-402.25931;0.00008;,
 143.09740;-280.89697;0.00001;,
 235.85960;-384.94131;0.00005;,
 164.69119;-268.80338;0.00001;,
 265.33069;-365.24896;0.00006;,
 185.26920;-255.05443;-0.00002;,
 293.16531;-343.30524;0.00004;,
 204.70551;-239.73276;0.00002;,
 319.19321;-319.24646;-0.00000;,
 222.87950;-222.93242;-0.00000;,
 343.25229;-293.21832;-0.00001;,
 239.67979;-204.75839;0.00001;,
 365.19571;-265.38367;0.00002;,
 255.00150;-185.32243;0.00002;,
 384.88800;-235.91254;-0.00001;,
 268.75049;-164.74409;0.00003;,
 402.20590;-204.98796;0.00003;,
 280.84409;-143.15019;0.00002;,
 417.04630;-172.79922;0.00005;,
 291.20581;-120.67453;-0.00002;,
 429.31351;-139.54561;0.00000;,
 299.77209;-97.45483;0.00000;,
 438.93521;-105.43216;0.00000;,
 306.49030;-73.63458;0.00001;,
 445.84979;-70.66869;0.00000;,
 311.31781;-49.36097;-0.00000;,
 450.01511;-35.47003;-0.00000;,
 314.22760;-24.78313;0.00000;,
 451.40720;-0.05300;0.00000;,
 315.19940;-0.05300;0.00000;,
 450.01511;35.36383;0.00000;,
 314.22760;24.67733;-0.00001;,
 445.84979;70.56268;-0.00000;,
 311.31781;49.25496;0.00000;,
 438.93549;105.32575;-0.00001;,
 306.49060;73.52866;-0.00000;,
 429.31369;139.43942;0.00000;,
 299.77219;97.34885;-0.00001;,
 417.04630;172.69312;-0.00001;,
 291.20599;120.56815;-0.00003;,
 402.20679;204.88171;-0.00002;,
 280.84421;143.04439;0.00001;,
 384.88800;235.80711;-0.00003;,
 268.75079;164.63806;-0.00001;,
 365.19650;265.27808;-0.00002;,
 255.00160;185.21651;-0.00004;,
 343.25311;293.11292;-0.00003;,
 239.67990;204.65216;0.00003;,
 319.19351;319.14041;0.00000;,
 222.87950;222.82674;-0.00002;,
 293.16559;343.19943;-0.00001;,
 204.70610;239.62645;-0.00003;,
 265.33090;365.14374;-0.00006;,
 185.26961;254.94894;-0.00003;,
 235.85980;384.83511;-0.00012;,
 164.69141;268.69815;-0.00001;,
 204.93520;402.15341;0.00001;,
 143.09760;280.79135;-0.00002;,
 172.74680;416.99377;-0.00002;,
 120.62180;291.15326;-0.00003;,
 139.49280;429.26154;-0.00002;,
 97.40220;299.71957;-0.00003;,
 105.37940;438.88321;-0.00006;,
 73.58210;306.43665;-0.00003;,
 70.61620;445.79749;-0.00006;,
 49.30840;311.26550;-0.00006;,
 35.41740;449.96255;-0.00004;,
 24.73050;314.17487;-0.00002;,
 0.00050;451.35461;0.00004;,
 0.00040;315.14691;-0.00005;,
 -35.41650;449.96255;-0.00004;,
 -24.72980;314.17487;-0.00002;,
 -70.61520;445.79749;-0.00006;,
 -49.30760;311.26550;-0.00006;,
 -105.37820;438.88336;-0.00000;,
 -73.58120;306.43674;-0.00002;,
 -139.49181;429.26154;-0.00002;,
 -97.40140;299.71973;-0.00003;,
 -172.74570;416.99396;-0.00000;,
 -120.62090;291.15350;-0.00007;,
 -204.93410;402.15341;0.00001;,
 -143.09689;280.79135;-0.00002;,
 -235.85941;384.83511;-0.00012;,
 -164.69060;268.69815;-0.00001;,
 -265.33051;365.14374;-0.00006;,
 -185.26910;254.94897;-0.00005;,
 -293.16531;343.20001;-0.00004;,
 -204.70461;239.62686;-0.00000;,
 -319.19312;319.14093;-0.00008;,
 -222.87910;222.82701;0.00002;,
 -343.25211;293.11310;0.00001;,
 -239.67909;204.65228;0.00001;,
 -365.19571;265.27820;0.00000;,
 -255.00130;185.21677;-0.00001;,
 -384.88730;235.80734;0.00001;,
 -268.75049;164.63841;-0.00003;,
 -402.20551;204.88193;-0.00002;,
 -280.84351;143.04456;0.00002;,
 -417.04611;172.69351;-0.00002;,
 -291.20541;120.56866;-0.00001;,
 -429.31360;139.43985;-0.00001;,
 -299.77191;97.34928;-0.00003;,
 -438.93521;105.32619;-0.00001;,
 -306.49030;73.52899;-0.00002;,
 -445.84991;70.56278;0.00000;,
 -311.31769;49.25527;-0.00001;,
 -450.01459;35.36414;-0.00001;,
 -314.22720;24.67733;-0.00001;,
 -451.40671;-0.05290;0.00000;,
 -315.19919;-0.05290;0.00000;;
 
 80;
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
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;122,124,125,123;,
 4;124,126,127,125;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;132,134,135,133;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,0,3,159;;
 
 MeshMaterialList {
  5;
  80;
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  4,
  4,
  4;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.103200;0.103200;0.103200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.100000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.019200;0.050400;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  80;
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000001;1.000000;,
  -0.000001;0.000001;1.000000;,
  -0.000000;0.000001;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000001;1.000000;,
  0.000001;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000001;0.000000;1.000000;,
  0.000001;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000001;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.000001;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000001;1.000000;,
  0.000001;0.000000;1.000000;,
  0.000001;-0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000000;0.000000;1.000000;,
  -0.000001;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000001;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000001;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000001;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000001;0.000000;1.000000;,
  0.000000;0.000001;1.000000;,
  0.000000;0.000001;1.000000;,
  0.000000;0.000001;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;;
  80;
  4;0,1,1,0;,
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
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,49,49,48;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,0,0,79;;
 }
 MeshTextureCoords {
  160;
  0.629810;0.853970;,
  0.628610;0.864120;,
  0.602880;0.860050;,
  0.603850;0.851920;,
  0.626610;0.874150;,
  0.601290;0.868070;,
  0.623840;0.883990;,
  0.599070;0.875940;,
  0.620300;0.893580;,
  0.596240;0.883610;,
  0.616020;0.902860;,
  0.592810;0.891040;,
  0.611020;0.911780;,
  0.588820;0.898180;,
  0.605340;0.920280;,
  0.584270;0.904980;,
  0.599010;0.928310;,
  0.579210;0.911400;,
  0.592070;0.935820;,
  0.573660;0.917410;,
  0.584560;0.942760;,
  0.567650;0.922960;,
  0.576530;0.949090;,
  0.561230;0.928020;,
  0.568030;0.954770;,
  0.554430;0.932570;,
  0.559110;0.959770;,
  0.547290;0.936560;,
  0.549830;0.964050;,
  0.539860;0.939990;,
  0.540240;0.967590;,
  0.532190;0.942820;,
  0.530400;0.970360;,
  0.524320;0.945040;,
  0.520370;0.972360;,
  0.516300;0.946630;,
  0.510220;0.973560;,
  0.508170;0.947600;,
  0.500000;0.973960;,
  0.500000;0.947920;,
  0.489780;0.973560;,
  0.491830;0.947600;,
  0.479630;0.972360;,
  0.483710;0.946630;,
  0.469600;0.970360;,
  0.475680;0.945040;,
  0.459760;0.967590;,
  0.467810;0.942820;,
  0.450170;0.964050;,
  0.460140;0.939990;,
  0.440890;0.959770;,
  0.452710;0.936560;,
  0.431970;0.954770;,
  0.445570;0.932570;,
  0.423470;0.949090;,
  0.438770;0.928020;,
  0.415440;0.942760;,
  0.432350;0.922960;,
  0.407930;0.935820;,
  0.426340;0.917410;,
  0.400990;0.928310;,
  0.420790;0.911400;,
  0.394660;0.920280;,
  0.415730;0.904980;,
  0.388980;0.911780;,
  0.411180;0.898180;,
  0.383980;0.902860;,
  0.407190;0.891040;,
  0.379700;0.893580;,
  0.403760;0.883610;,
  0.376170;0.883990;,
  0.400930;0.875940;,
  0.373390;0.874150;,
  0.398710;0.868070;,
  0.371390;0.864120;,
  0.397120;0.860050;,
  0.370190;0.853970;,
  0.396150;0.851920;,
  0.369790;0.843750;,
  0.395830;0.843750;,
  0.370190;0.833530;,
  0.396150;0.835580;,
  0.371390;0.823380;,
  0.397120;0.827450;,
  0.373390;0.813350;,
  0.398710;0.819430;,
  0.376170;0.803510;,
  0.400930;0.811560;,
  0.379700;0.793920;,
  0.403760;0.803890;,
  0.383980;0.784640;,
  0.407190;0.796460;,
  0.388980;0.775720;,
  0.411180;0.789320;,
  0.394660;0.767220;,
  0.415730;0.782520;,
  0.400990;0.759190;,
  0.420790;0.776100;,
  0.407930;0.751680;,
  0.426340;0.770090;,
  0.415440;0.744740;,
  0.432350;0.764540;,
  0.423470;0.738410;,
  0.438770;0.759480;,
  0.431970;0.732730;,
  0.445570;0.754930;,
  0.440890;0.727730;,
  0.452710;0.750940;,
  0.450170;0.723450;,
  0.460140;0.747510;,
  0.459760;0.719910;,
  0.467810;0.744680;,
  0.469600;0.717140;,
  0.475680;0.742460;,
  0.479630;0.715140;,
  0.483710;0.740870;,
  0.489780;0.713940;,
  0.491830;0.739900;,
  0.500000;0.713540;,
  0.500000;0.739580;,
  0.510220;0.713940;,
  0.508170;0.739900;,
  0.520370;0.715140;,
  0.516300;0.740870;,
  0.530400;0.717140;,
  0.524320;0.742460;,
  0.540240;0.719910;,
  0.532190;0.744680;,
  0.549830;0.723450;,
  0.539860;0.747510;,
  0.559110;0.727730;,
  0.547290;0.750940;,
  0.568030;0.732730;,
  0.554430;0.754930;,
  0.576530;0.738410;,
  0.561230;0.759480;,
  0.584560;0.744740;,
  0.567650;0.764540;,
  0.592070;0.751680;,
  0.573660;0.770090;,
  0.599010;0.759190;,
  0.579210;0.776100;,
  0.605340;0.767220;,
  0.584270;0.782520;,
  0.611020;0.775720;,
  0.588820;0.789320;,
  0.616020;0.784640;,
  0.592810;0.796460;,
  0.620300;0.793920;,
  0.596240;0.803890;,
  0.623840;0.803510;,
  0.599070;0.811560;,
  0.626610;0.813350;,
  0.601290;0.819430;,
  0.628610;0.823380;,
  0.602880;0.827450;,
  0.629810;0.833530;,
  0.603850;0.835580;,
  0.630210;0.843750;,
  0.604170;0.843750;;
 }
}

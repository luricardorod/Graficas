xof 0303txt 0032
template KeyValuePair {
 <26e6b1c3-3d4d-4a1d-a437-b33668ffa1c2>
 STRING key;
 STRING value;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template ObjectMatrixComment {
 <95a48e28-7ef4-4419-a16a-ba9dbdf0d2bc>
 Matrix4x4 objectMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template VertexElement {
 <f752461c-1e23-48f6-b9f8-8350850f336f>
 DWORD Type;
 DWORD Method;
 DWORD Usage;
 DWORD UsageIndex;
}

template DeclData {
 <bf22e553-292c-4781-9fea-62bd554bdd93>
 DWORD nElements;
 array VertexElement Elements[nElements];
 DWORD nDWords;
 array DWORD data[nDWords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template EffectInstance {
 <e331f7e4-0559-4cc2-8e99-1cec1657928f>
 STRING EffectFilename;
 [...]
}

template EffectParamDWord {
 <e13963bc-ae51-4c5d-b00f-cfa3a9d97ce5>
 STRING ParamName;
 DWORD Value;
}

template EffectParamFloats {
 <3014b9a0-62f5-478c-9b86-e4ac9f4e418b>
 STRING ParamName;
 DWORD nFloats;
 array FLOAT Floats[nFloats];
}

template EffectParamString {
 <1dbc4c88-94c1-46ee-9076-2c28818c9481>
 STRING ParamName;
 STRING Value;
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}


KeyValuePair {
 "Date";
 "2017-08-16 10:33:46";
}

KeyValuePair {
 "File";
 "";
}

KeyValuePair {
 "User";
 "F_A_R";
}

KeyValuePair {
 "CoreTime";
 "0";
}

Frame pPlane11 {
 

 FrameTransformMatrix relative {
  0.010000,0.000000,0.000000,0.000000,0.000000,0.010000,0.000000,0.000000,0.000000,-0.000000,0.010000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 ObjectMatrixComment object {
  0.010000,0.000000,0.000000,0.000000,0.000000,0.010000,0.000000,0.000000,0.000000,-0.000000,0.010000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh mesh_pPlane11 {
  25;
  -1.250000;14.929999;1.250002;,
  -1.250000;14.929999;0.625002;,
  -0.625000;14.929999;0.625002;,
  -0.625000;14.929999;1.250002;,
  -1.250000;14.929999;0.000002;,
  -0.625000;14.929999;0.000002;,
  0.000000;14.929999;0.625002;,
  0.000000;14.929999;1.250002;,
  0.000000;14.929999;0.000002;,
  -1.250000;14.929999;-0.624998;,
  -1.250000;14.929999;-1.249998;,
  -0.625000;14.929999;-1.249998;,
  -0.625000;14.929999;-0.624998;,
  0.000000;14.929999;-1.249998;,
  0.000000;14.929999;-0.624998;,
  1.250000;14.929999;-1.249998;,
  1.250000;14.929999;-0.624998;,
  0.625000;14.929999;-0.624998;,
  0.625000;14.929999;-1.249998;,
  1.250000;14.929999;0.000002;,
  0.625000;14.929999;0.000002;,
  1.250000;14.929999;0.625002;,
  1.250000;14.929999;1.250002;,
  0.625000;14.929999;1.250002;,
  0.625000;14.929999;0.625002;;
  32;
  3;0,1,2;,
  3;2,3,0;,
  3;1,4,5;,
  3;5,2,1;,
  3;3,2,6;,
  3;6,7,3;,
  3;2,5,8;,
  3;8,6,2;,
  3;9,10,11;,
  3;11,12,9;,
  3;12,11,13;,
  3;13,14,12;,
  3;4,9,12;,
  3;12,5,4;,
  3;5,12,14;,
  3;14,8,5;,
  3;15,16,17;,
  3;17,18,15;,
  3;16,19,20;,
  3;20,17,16;,
  3;18,17,14;,
  3;14,13,18;,
  3;17,20,8;,
  3;8,14,17;,
  3;21,22,23;,
  3;23,24,21;,
  3;24,23,7;,
  3;7,6,24;,
  3;19,21,24;,
  3;24,20,19;,
  3;20,24,6;,
  3;6,8,20;;

  MeshNormals normals {
   25;
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;,
   0.000000;-1.000000;-0.000000;;
   32;
   3;0,1,2;,
   3;2,3,0;,
   3;1,4,5;,
   3;5,2,1;,
   3;3,2,6;,
   3;6,7,3;,
   3;2,5,8;,
   3;8,6,2;,
   3;9,10,11;,
   3;11,12,9;,
   3;12,11,13;,
   3;13,14,12;,
   3;4,9,12;,
   3;12,5,4;,
   3;5,12,14;,
   3;14,8,5;,
   3;15,16,17;,
   3;17,18,15;,
   3;16,19,20;,
   3;20,17,16;,
   3;18,17,14;,
   3;14,13,18;,
   3;17,20,8;,
   3;8,14,17;,
   3;21,22,23;,
   3;23,24,21;,
   3;24,23,7;,
   3;7,6,24;,
   3;19,21,24;,
   3;24,20,19;,
   3;20,24,6;,
   3;6,8,20;;
  }

  MeshTextureCoords tc0 {
   25;
   0.800088;0.715560;,
   0.800088;0.760836;,
   0.845364;0.760836;,
   0.845364;0.715560;,
   0.800088;0.806112;,
   0.845364;0.806112;,
   0.890640;0.760836;,
   0.890640;0.715560;,
   0.890640;0.806112;,
   0.800088;0.851388;,
   0.800088;0.896664;,
   0.845364;0.896664;,
   0.845364;0.851388;,
   0.890640;0.896664;,
   0.890640;0.851388;,
   0.981192;0.896664;,
   0.981192;0.851388;,
   0.935916;0.851388;,
   0.935916;0.896664;,
   0.981192;0.806112;,
   0.935916;0.806112;,
   0.981192;0.760836;,
   0.981192;0.715560;,
   0.935916;0.715560;,
   0.935916;0.760836;;
  }

  DeclData {
   2;
   2;0;7;0;,
   2;0;6;0;;
   150;
   875884394,
   3019898880,
   1065353216,
   1065353216,
   682946410,
   3023368042,
   884273003,
   3019898880,
   1065353216,
   1065353216,
   691335019,
   3031756651,
   875884393,
   3019898880,
   1065353216,
   1065353216,
   682946409,
   3023368041,
   0,
   3019898880,
   1065353216,
   1065353216,
   0,
   0,
   884273003,
   3019898880,
   1065353216,
   1065353216,
   691335019,
   3031756651,
   886249297,
   3019898880,
   1065353216,
   1065353216,
   693311313,
   3033732945,
   863059773,
   3019898880,
   1065353216,
   1065353216,
   670121789,
   3010543421,
   0,
   3019898880,
   1065353216,
   1065353216,
   0,
   0,
   884767080,
   3019898880,
   1065353216,
   1065353216,
   691829096,
   3032250728,
   889697166,
   3019898880,
   1065353216,
   1065353216,
   696759182,
   3037180814,
   895626050,
   3019898880,
   1065353216,
   1065353216,
   702688066,
   3043109698,
   891673463,
   3019898880,
   1065353216,
   1065353216,
   698735479,
   3039157111,
   889697168,
   3019898880,
   1065353216,
   1065353216,
   696759184,
   3037180816,
   892661613,
   3019898880,
   1065353216,
   1065353216,
   699723629,
   3040145261,
   892167538,
   3019898880,
   1065353216,
   1065353216,
   699229554,
   3039651186,
   890438282,
   3019898880,
   1065353216,
   1065353216,
   697500298,
   3037921930,
   882296712,
   3019898880,
   1065353216,
   1065353216,
   689358728,
   3029780360,
   890191244,
   3019898880,
   1065353216,
   1065353216,
   697253260,
   3037674892,
   894143836,
   3019898880,
   1065353216,
   1065353216,
   701205852,
   3041627484,
   884273008,
   3019898880,
   1065353216,
   1065353216,
   691335024,
   3031756656,
   881802637,
   3019898880,
   1065353216,
   1065353216,
   688864653,
   3029286285,
   879836989,
   3019898880,
   1065353216,
   1065353216,
   686899005,
   3027320637,
   0,
   3019898880,
   1065353216,
   1065353216,
   0,
   0,
   871448380,
   3019898880,
   1065353216,
   1065353216,
   678510396,
   3018932028,
   875884398,
   3019898880,
   1065353216,
   1065353216,
   682946414,
   3023368046;
  }

  MeshMaterialList mtls {
   1;
   32;
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
   0;

   Material Dflt_Material {
    0.800000;0.800000;0.800000;1.000000;;
    16.000000;
    1.000000;1.000000;1.000000;;
    0.000000;0.000000;0.000000;;

    EffectInstance Effect {
     "Xoliulshader_1.3.fx";

     EffectParamDWord {
      "light1_Position";
      0;
     }

     EffectParamDWord {
      "__PlaceHolder_255_shadowTerm1";
      0;
     }

     EffectParamDWord {
      "bUseShadow1";
      0;
     }

     EffectParamFloats {
      "Shadow1Soft";
      1;
      0.000000;
     }

     EffectParamFloats {
      "Shadow1Strength";
      1;
      1.000000;
     }

     EffectParamFloats {
      "DistanceBlur";
      1;
      3.000000;
     }

     EffectParamDWord {
      "light2_Position";
      0;
     }

     EffectParamDWord {
      "light3_Position";
      0;
     }

     EffectParamDWord {
      "bUseHalfLambert";
      0;
     }

     EffectParamFloats {
      "HalfLambertPower";
      1;
      2.000000;
     }

     EffectParamFloats {
      "ambientcolor";
      4;
      0.000000,
      0.000000,
      0.000000,
      0.000000;
     }

     EffectParamDWord {
      "bUseIBL";
      0;
     }

     EffectParamDWord {
      "bUseIBLCubeMap";
      0;
     }

     EffectParamFloats {
      "IBLBlur";
      1;
      6.000000;
     }

     EffectParamFloats {
      "IBLmultiplier";
      1;
      0.500000;
     }

     EffectParamDWord {
      "numberOfActiveLights";
      1;
     }

     EffectParamDWord {
      "bUseDiffuseMap";
      1;
     }

     EffectParamFloats {
      "diffuseColor";
      4;
      0.500000,
      0.500000,
      0.500000,
      1.000000;
     }

     EffectParamString {
      "diffuseMap";
      "Ventana_Base_Color.tga";
     }

     EffectParamDWord {
      "bColorDiffuse";
      0;
     }

     EffectParamDWord {
      "bUseAlpha";
      0;
     }

     EffectParamFloats {
      "GlobalOpacity";
      1;
      1.000000;
     }

     EffectParamDWord {
      "bUseSpecMap";
      1;
     }

     EffectParamFloats {
      "specularColor";
      4;
      1.000000,
      1.000000,
      1.000000,
      1.000000;
     }

     EffectParamFloats {
      "speclevel";
      1;
      1.000000;
     }

     EffectParamString {
      "specularMap";
      "Ventana_Specular.tga";
     }

     EffectParamDWord {
      "bUseGlossMap";
      1;
     }

     EffectParamString {
      "glossMap";
      "Ventana_Glossiness.tga";
     }

     EffectParamFloats {
      "glossiness";
      1;
      25.000000;
     }

     EffectParamFloats {
      "glossoffset";
      1;
      10.000000;
     }

     EffectParamDWord {
      "bUseNormalMap";
      1;
     }

     EffectParamDWord {
      "bUseObjectNormals";
      0;
     }

     EffectParamString {
      "normalMap";
      "Ventana_Normal.tga";
     }

     EffectParamDWord {
      "bFlipGreenChannel";
      0;
     }

     EffectParamDWord {
      "bUseSIMap";
      0;
     }

     EffectParamFloats {
      "siMapMult";
      1;
      1.000000;
     }

     EffectParamFloats {
      "siLevel";
      1;
      0.000000;
     }

     EffectParamDWord {
      "bUseFresnel";
      0;
     }

     EffectParamDWord {
      "bAlphaMasksFresnel";
      0;
     }

     EffectParamFloats {
      "FresnelPower";
      1;
      3.000000;
     }

     EffectParamFloats {
      "FresnelBias";
      1;
      0.000000;
     }

     EffectParamFloats {
      "FresnelMult";
      1;
      2.000000;
     }

     EffectParamFloats {
      "FresnelColor";
      4;
      1.000000,
      1.000000,
      1.000000,
      0.000000;
     }

     EffectParamFloats {
      "FresnelMaskHardness";
      1;
      4.000000;
     }

     EffectParamDWord {
      "bUseWorldMask";
      1;
     }

     EffectParamDWord {
      "bUseReflMap";
      0;
     }

     EffectParamDWord {
      "bUseCubeMap";
      0;
     }

     EffectParamFloats {
      "CubeMapBlur";
      1;
      0.000000;
     }

     EffectParamDWord {
      "bUseReflGloss";
      0;
     }
    }

    TextureFilename Diffuse {
     "Ventana_Base_Color.tga";
    }
   }
  }
 }
}
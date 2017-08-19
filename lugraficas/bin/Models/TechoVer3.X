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
 "2017-08-16 10:35:07";
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

Frame pPlane12 {
 

 FrameTransformMatrix relative {
  0.010000,0.000000,0.000000,0.000000,0.000000,0.010000,0.000000,0.000000,0.000000,-0.000000,0.010000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 ObjectMatrixComment object {
  0.010000,0.000000,0.000000,0.000000,0.000000,0.010000,0.000000,0.000000,0.000000,-0.000000,0.010000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh mesh_pPlane12 {
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
   0.981192;0.299129;,
   0.935916;0.299129;,
   0.935916;0.344405;,
   0.981192;0.344405;,
   0.890640;0.299129;,
   0.890640;0.344405;,
   0.935916;0.389681;,
   0.981192;0.389681;,
   0.890640;0.389681;,
   0.845364;0.299129;,
   0.800088;0.299129;,
   0.800088;0.344405;,
   0.845364;0.344405;,
   0.800088;0.389681;,
   0.845364;0.389681;,
   0.800088;0.480233;,
   0.845364;0.480233;,
   0.845364;0.434957;,
   0.800088;0.434957;,
   0.890640;0.480233;,
   0.890640;0.434957;,
   0.935916;0.480233;,
   0.981192;0.480233;,
   0.981192;0.434957;,
   0.935916;0.434957;;
  }

  DeclData {
   2;
   2;0;7;0;,
   2;0;6;0;;
   150;
   3212836864,
   2810385007,
   855839343,
   855839343,
   3019898880,
   1065353216,
   3212836864,
   0,
   0,
   0,
   3019898880,
   1065353216,
   3212836864,
   2803428055,
   848882391,
   848882391,
   3019898880,
   1065353216,
   3212836864,
   2816111631,
   861565967,
   861565967,
   3019898880,
   1065353216,
   3212836864,
   2842400703,
   887855039,
   887855039,
   3019898880,
   1065353216,
   3212836864,
   2842490183,
   887944519,
   887944519,
   3019898880,
   1065353216,
   3212836864,
   2801996399,
   847450735,
   847450735,
   3019898880,
   1065353216,
   3212836864,
   2813248319,
   858702655,
   858702655,
   3019898880,
   1065353216,
   3212836864,
   0,
   0,
   0,
   3019898880,
   1065353216,
   3212836864,
   695632860,
   3036054492,
   3036054492,
   3019898880,
   1065353216,
   3212836864,
   0,
   0,
   0,
   3019898880,
   1065353216,
   3212836864,
   704021469,
   3044443101,
   3044443101,
   3019898880,
   1065353216,
   3212836864,
   660239018,
   3000660650,
   3000660650,
   3019898880,
   1065353216,
   3212836864,
   696301576,
   3036723208,
   3036723208,
   3019898880,
   1065353216,
   3212836864,
   2832938357,
   878392693,
   878392693,
   3019898880,
   1065353216,
   3212836864,
   662901358,
   3003322990,
   3003322990,
   3019898880,
   1065353216,
   3212836864,
   0,
   0,
   0,
   3019898880,
   1065353216,
   3212836864,
   655944406,
   2996366038,
   2996366038,
   3019898880,
   1065353216,
   3212836864,
   668627982,
   3009049614,
   3009049614,
   3019898880,
   1065353216,
   3212836864,
   0,
   0,
   0,
   3019898880,
   1065353216,
   3212836864,
   632210239,
   2972631871,
   2972631871,
   3019898880,
   1065353216,
   3212836864,
   2804859711,
   850314047,
   850314047,
   3019898880,
   1065353216,
   3212836864,
   0,
   0,
   0,
   3019898880,
   1065353216,
   3212836864,
   2813248319,
   858702655,
   858702655,
   3019898880,
   1065353216,
   3212836864,
   2807723023,
   853177359,
   853177359,
   3019898880,
   1065353216;
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
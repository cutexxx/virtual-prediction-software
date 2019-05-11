#if !defined(AFX_T3DMODEL_H_INCLUDED_)
#define AFX_T3DMODEL_H_INCLUDED_

/***************************************************************
本文件所存储为三维模型文件格式相关类及其函数的的定义

**************************************************************/
#include "StdAfx.h"

// 四维向量类，用于记录包含alpha通道的RGBA色彩
class CVector4 
{
public:
	float x, y, z , a ;
	
	CVector4()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
		a = 1.0;
	}
	virtual void SavetoFile(FILE *fp)
	{
		fwrite(&x,sizeof(float),1,fp);
		fwrite(&y,sizeof(float),1,fp);
		fwrite(&z,sizeof(float),1,fp);
		fwrite(&a,sizeof(float),1,fp);
	}
	virtual void LoadFromFile(FILE *fp)
	{
		fread(&x,sizeof(float),1,fp);
		fread(&y,sizeof(float),1,fp);
		fread(&z,sizeof(float),1,fp);
		fread(&a,sizeof(float),1,fp);
	}
};

// 三维向量类，用于记录位置，法向量，RGB颜色
class CVector3 
{
public:
	float x, y, z;
	
	CVector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	CVector3(float xi,float yi,float zi)
	{
		x = xi;
		y = yi;
		z = zi;
	}
	virtual void SavetoFile(FILE *fp)
	{
		fwrite(&x,sizeof(float),1,fp);
		fwrite(&y,sizeof(float),1,fp);
		fwrite(&z,sizeof(float),1,fp);
	}
	virtual void LoadFromFile(FILE *fp)
	{
		fread(&x,sizeof(float),1,fp);
		fread(&y,sizeof(float),1,fp);
		fread(&z,sizeof(float),1,fp);
	}
	
	void copy(CVector3* c)//复制三维向量
	{
		x = c->x;
		y = c->y;
		z = c->z;
	}
	
	void exchangeYZ()//对换yz坐标，用于由max的左手系转为OpenGL的右手系
	{
		float tmp = z;
		z=-y;
		y=tmp;
	}

	CVector3 operator / (float d)
	{
		x = x/d;
		y = y/d;
		z = z/d;
		return (*this);
	}
};

// 二维向量类，用于记录纹理坐标
class CVector2 
{
public:
	float x, y;
	
	CVector2()
	{
		x = 0;
		y = 0;
	}

	virtual void SavetoFile(FILE *fp)
	{
		fwrite(&x,sizeof(float),1,fp);
		fwrite(&y,sizeof(float),1,fp);
	}

	virtual void LoadFromFile(FILE *fp)
	{
		fread(&x,sizeof(float),1,fp);
		fread(&y,sizeof(float),1,fp);
	}
	
	void copy(CVector2* c)
	{
		x = c->x;
		y = c->y;
	}
};

/***********************************************************
保存面中的顶点信息及纹理坐标数组，从此信息我们
能知道由哪些顶点构成了哪些面
***********************************************************/
class tFace
{
public:
	int vertIndex[3];			// 存放顶点索引
	int normalIndex[3];			// 存放法线索引
	int coordIndex[3];			// 存放纹理索引
	
	tFace()
	{
		vertIndex[0] = vertIndex[1] = vertIndex[2] = 0;
		normalIndex[0] = normalIndex[1] = normalIndex[2] = 0;
		coordIndex[0] = coordIndex[1] = coordIndex[2] = 0;
	}
	virtual void SavetoFile(FILE *fp)
	{
		fwrite(&vertIndex,sizeof(int),3,fp);
		fwrite(&normalIndex,sizeof(int),3,fp);
		fwrite(&coordIndex,sizeof(int),3,fp);
	}
	virtual void LoadFromFile(FILE *fp)
	{
		fread(&vertIndex,sizeof(int),3,fp);
		fread(&normalIndex,sizeof(int),3,fp);
		fread(&coordIndex,sizeof(int),3,fp);
	}	
};

/*******************************************************************
为实现纹理内置，建立位图类
以非压缩方式记录二维纹理的rgba位图
*******************************************************************/
class tInnerBitmap
{
public:
	
	int width;	//位图宽度
	int height;	//位图高度
	int aspect;	//纵横比
	unsigned char* pixel;//位图序列存储
	
	tInnerBitmap()
	{
		width = height = 0;
		aspect= 0;
		pixel = NULL;
	}
	~tInnerBitmap()
	{
		delete[] pixel;
	}
	
	virtual void SavetoFile(FILE *fp)
	{
		
		fwrite(&width,sizeof(int),1,fp);
		fwrite(&height,sizeof(int),1,fp);
		fwrite(&aspect,sizeof(int),1,fp);
		fwrite(pixel,sizeof(unsigned char),width*height*4,fp);
		
	}
	
	virtual void LoadFromFile(FILE *fp)
	{
		fread(&width,sizeof(int),1,fp);
		fread(&height,sizeof(int),1,fp);
		fread(&aspect,sizeof(int),1,fp);
		pixel = new unsigned char[width*height*4];
		fread(pixel,sizeof(unsigned char),width*height*4,fp);
	}
};

/*******************************************************************
存储纹理的信息，它有可能只是一些颜色信息。
*******************************************************************/
class tMaterialInfo
{
public:
	char  strName[255];			// The texture name
	char  strFile[255];			// The texture file name (If this is set it's a texture map)
//	BYTE  color[3];				// The color of the object (R, G, B)
	bool  bHasTexture;          //纹理中是否有Texture(否则只包含RGB信息)
	int   texureId;				// the texture ID
	unsigned int  bindId;
	CVector4	Ambient;			//环境光反射色
	CVector4	Diffuse;			//漫反射光反射色
	CVector4	Specular;			//镜面反射光反射色
	float		Shininess;			//反射指数
	bool		SelfIllum;			//材质是否发光
	CVector4	Emission;			//材质发光色

	float uTile;				// u tiling of texture  (Currently not used)
	float vTile;				// v tiling of texture	(Currently not used)
	float uOffset;			    // u offset of texture	(Currently not used)
	float vOffset;				// v offset of texture	(Currently not used)

	tInnerBitmap* ibmp;			//内置位图
public:
	tMaterialInfo()
	{
		bHasTexture = false;
		texureId = -1;
		SelfIllum = false;
		uTile = vTile = uOffset = vOffset = 0.0;
		ibmp = NULL;
		Shininess = 0.3;
	}
	virtual void SavetoFile(FILE *fp)
	{
		fwrite(&strName,sizeof(char),255,fp);
		fwrite(&strFile,sizeof(char),255,fp);
//		fwrite(&color,sizeof(BYTE),3,fp);
		fwrite(&bHasTexture,sizeof(bool),1,fp);
		fwrite(&texureId,sizeof(int),1,fp);

		Ambient.SavetoFile(fp);
		Diffuse.SavetoFile(fp);
		Specular.SavetoFile(fp);
		fwrite(&Shininess,sizeof(float),1,fp);
		fwrite(&SelfIllum,sizeof(bool),1,fp);
		Emission.SavetoFile(fp);
		

		fwrite(&uTile,sizeof(float),1,fp);
		fwrite(&vTile,sizeof(float),1,fp);
		fwrite(&uOffset,sizeof(float),1,fp);
		fwrite(&vOffset,sizeof(float),1,fp);

		if(bHasTexture)
			ibmp->SavetoFile(fp);
	}
	virtual void LoadFromFile(FILE *fp)
	{
		fread(&strName,sizeof(char),255,fp);
		fread(&strFile,sizeof(char),255,fp);
//		fread(&color,sizeof(BYTE),3,fp);
		fread(&bHasTexture,sizeof(bool),1,fp);
		fread(&texureId,sizeof(int),1,fp);

		Ambient.LoadFromFile(fp);
		Diffuse.LoadFromFile(fp);
		Specular.LoadFromFile(fp);
		fread(&Shininess,sizeof(float),1,fp);
		fread(&SelfIllum,sizeof(bool),1,fp);
		Emission.LoadFromFile(fp);

		fread(&uTile,sizeof(float),1,fp);
		fread(&vTile,sizeof(float),1,fp);
		fread(&uOffset,sizeof(float),1,fp);
		fread(&vOffset,sizeof(float),1,fp);

		if(bHasTexture)
		{
			ibmp = new tInnerBitmap;
			ibmp->LoadFromFile(fp);	
		}

		glGenTextures(1,&bindId);
		glBindTexture(GL_TEXTURE_2D,bindId);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT); 
		gluBuild2DMipmaps(GL_TEXTURE_2D,4,
			ibmp->height,ibmp->width,GL_RGBA,GL_UNSIGNED_BYTE,
			ibmp->pixel);
	}
};


/***********************************************************************
存储模型中每个物体的信息
***********************************************************************/
//注意：赋值时要给pVerts、pFaces、pNormals分配空间
class t3DObject 
{
public:
	int  numOfVerts;			// The number of verts in the model
	int  numOfNormals;			// The number of normals in the model
	int  numOfFaces;			// The number of faces in the model
	char strName[255];			// The name of the object
	CVector3  *pVerts;			// The object's vertices
	tFace *pFaces;				// The faces information of the object

	CVector3  *pNormals;		// The object's normals
	bool bHasMaterial;			// This is TRUE if there is a material for this object
	BYTE  color[3];				// The color of the object (R, G, B)
	int  numTexVerts;			// The number of texture coordinates
	int  materialID;			// The texture ID to use, which is the index into our texture array
	CVector2  *pTexVerts;		// The texture's UV coordinates
	
	int	movement;				// 动态属性（本程序独有）
	int* vertMovement;			// 定点动态属性（本程序独有）
	
	t3DObject()
	{
		numOfVerts = 0;
		numOfFaces = 0;
		numTexVerts = 0;
		bHasMaterial = false;
		color[0] = color[1] = color[2] = 0;
		materialID = -1;
		pVerts = NULL;
		pFaces = NULL;	
		pNormals = NULL;
		pTexVerts = NULL;
		vertMovement = NULL;
	}
	virtual void SavetoFile(FILE *fp)
	{
		fwrite(&numOfVerts,sizeof(int),1,fp);
		fwrite(&numOfNormals,sizeof(int),1,fp);
		fwrite(&numOfFaces,sizeof(int),1,fp);
		fwrite(&numTexVerts,sizeof(int),1,fp);

		fwrite(&strName,sizeof(char),255,fp);
		for(int i=0; i<numOfVerts; i++)
		{
			pVerts[i].SavetoFile(fp);				
		}
		for(i=0; i<numOfNormals; i++)
		{			
			pNormals[i].SavetoFile(fp);	
		}
		for(i=0; i<numOfFaces; i++)
		{
			pFaces[i].SavetoFile(fp);
		}
		for(i=0; i<numTexVerts; i++)
		{
			pTexVerts[i].SavetoFile(fp);
		}
		fwrite(&bHasMaterial,sizeof(bool),1,fp);
		fwrite(&color,sizeof(BYTE),3,fp);	
		fwrite(&materialID,sizeof(int),1,fp);
	}
	
	virtual void LoadFromFile(FILE *fp)
	{
		fread(&numOfVerts,sizeof(int),1,fp);
		fread(&numOfNormals,sizeof(int),1,fp);
		fread(&numOfFaces,sizeof(int),1,fp);
		fread(&numTexVerts,sizeof(int),1,fp);

		fread(&strName,sizeof(char),255,fp);

		//初始化
		pVerts = new CVector3[numOfVerts];
		pFaces = new tFace[numOfFaces];
		pNormals = new CVector3[numOfNormals];
		pTexVerts = new CVector2[numTexVerts];

		for(int i=0; i<numOfVerts; i++)
		{ 
			pVerts[i].LoadFromFile(fp);
			pVerts[i].exchangeYZ();
		}
		for(i=0; i<numOfNormals; i++)
		{			
			pNormals[i].LoadFromFile(fp);	
			pNormals[i].exchangeYZ();
		}
		for(i=0; i<numOfFaces; i++)
		{
			pFaces[i].LoadFromFile(fp);
		}
		for(i=0; i<numTexVerts; i++)
		{
			pTexVerts[i].LoadFromFile(fp);
		}
		fread(&bHasMaterial,sizeof(bool),1,fp);
		fread(&color,sizeof(BYTE),3,fp);	
		fread(&materialID,sizeof(int),1,fp);
	}
	
	//以下包含一些向量代数相关函数
	void normalize(CVector3* a)//单位化向量
	{
		float tmp = sqrt(a->x*a->x + a->y* a->y + a->z*a->z);
		a->x = a->x/tmp;
		a->y = a->y/tmp;
		a->z = a->z/tmp;
	}
	
	void VectProduct(CVector3* c, CVector3 a, CVector3 b) //aXb = c
	{
		c->x = a.y*b.z - a.z*b.y;
		c->y = a.z*b.x - a.x*b.z;
		c->z = a.x*b.y - a.y*b.x;
	}
	
	void getDirection(CVector3* n,CVector3 a,CVector3 b)//求出ba的方向
	{
		n->x = b.x - a.x;
		n->y = b.y - a.y;
		n->z = b.z - a.z;
	}
	
	void getPosition(CVector3 * tmp)//获取标定用矩形的中心位置
	{
		tmp->x = (pVerts[0].x + pVerts[1].x + pVerts[2].x + pVerts[3].x)/4.0f;
		tmp->y = (pVerts[0].y + pVerts[1].y + pVerts[2].y + pVerts[3].y)/4.0f;
		tmp->z = (pVerts[0].z + pVerts[1].z + pVerts[2].z + pVerts[3].z)/4.0f;
	}
	
	void getNormal(CVector3* tmpNor)//获取标定用矩形的法线方向
	{
		CVector3 tmpAB,tmpCB;//存储方向的临时变量
		getDirection(&tmpAB,pVerts[1],pVerts[0]);
		getDirection(&tmpCB,pVerts[1],pVerts[2]);
		
		VectProduct(tmpNor,tmpCB,tmpAB);
		normalize(tmpNor);
	}
};


/***********************************************************************
存储模型中每个光源的信息
***********************************************************************/
class tLight
{
public:
	char		strName[255];		//光源名称

	CVector4	Position;			//光源位置
	CVector3	Direction;			//聚光方向

	float		Exponent;			//聚光指数
	float		CutOff;				//截至角
	CVector3	Attenuation;		//衰减因子，依次为常数、线性及二次因子

	CVector4	Ambient;			//环境光分量强度
	CVector4	Diffuse;			//漫反射光分量强度
	CVector4	Specular;			//镜面反射光分量强度

	bool		LightOn;			//光源是否打开

public:
	tLight()
	{
		//以下均按OpenGL默认值初始化
		Direction.z = -1.0;

		Exponent = 0.0;
		CutOff = 180.0;
		Attenuation.x = 1.0;

		Ambient.a =1.0;
		Diffuse.x = Diffuse.y = Diffuse.z = Diffuse.a =0.0;
		Specular.x = Specular.y = Specular.z = Specular.a =0.0;

		LightOn = true;
	}
	virtual void SavetoFile(FILE *fp)
	{
		fwrite(&strName,sizeof(char),255,fp);

		Position.SavetoFile(fp);
		Direction.SavetoFile(fp);

		fwrite(&Exponent,sizeof(float),1,fp);
		fwrite(&CutOff,sizeof(float),1,fp);
		Attenuation.SavetoFile(fp);

		Ambient.SavetoFile(fp);
		Diffuse.SavetoFile(fp);	
		Specular.SavetoFile(fp);

		fwrite(&LightOn,sizeof(bool),1,fp);
	}
	virtual void LoadFromFile(FILE *fp)
	{
		fread(&strName,sizeof(char),255,fp);

		Position.LoadFromFile(fp);
		Direction.LoadFromFile(fp);

		fread(&Exponent,sizeof(float),1,fp);
		fread(&CutOff,sizeof(float),1,fp);
		Attenuation.LoadFromFile(fp);

		Ambient.LoadFromFile(fp);
		Diffuse.LoadFromFile(fp);
		Specular.LoadFromFile(fp);

		fread(&LightOn,sizeof(bool),1,fp);
	}
};

/***********************************************************************
存储模型中每个相机的信息
***********************************************************************/
class tCamera
{
public:
	char		strName[255];		//相机名称

	CVector3	Position;			//光源位置
	CVector3	Direction;			//聚光方向

	float		NearPlane;			//近剪切面	
	float		FarPlane;			//远剪切面
	float		Fov;				//视角弧度
		
	BOOL		IsOrtho;			//用途不明

public:
	tCamera()
	{
		//初始化
		Direction.z = -1.0;
		Fov = 45.0/180.0*3.14159;
		NearPlane = 1.0;
		FarPlane = 1000.0;
		IsOrtho = true;
		
	}
	virtual void SavetoFile(FILE *fp)
	{
		fwrite(&strName,sizeof(char),255,fp);

		Position.SavetoFile(fp);
		Direction.SavetoFile(fp);

		fwrite(&NearPlane,sizeof(float),1,fp);
		fwrite(&FarPlane,sizeof(float),1,fp);
		fwrite(&Fov,sizeof(float),1,fp);

		fwrite(&IsOrtho,sizeof(bool),1,fp);
	}
	virtual void LoadFromFile(FILE *fp)
	{
		fread(&strName,sizeof(char),255,fp);

		Position.LoadFromFile(fp);
		Direction.LoadFromFile(fp);

		fread(&NearPlane,sizeof(float),1,fp);
		fread(&FarPlane,sizeof(float),1,fp);
		fread(&Fov,sizeof(float),1,fp);

		fread(&IsOrtho,sizeof(bool),1,fp);
	}
};

/**********************************************************************************
存储整个模型文件的信息 
**********************************************************************************/
class t3DModel 
{
public:
	int numOfObjects;					// 模型文件中的物体数量
	vector<t3DObject> pObject;			// 模型文件中的物体表
	
	int numOfMaterials;                 // 模型文件中的材质数量
	vector<tMaterialInfo> pMaterials;	// 模型文件中的材质表
	
	int numOfLights;					// The number of lights for the model
	vector<tLight> pLights;				// The light list for our model

	int numOfCameras;					// The number of Cameras for the model
	vector<tCamera> pCamera;			// The Camera list for our model
public:
	t3DModel()
	{
		numOfObjects = 0;
		numOfMaterials = 0;
		numOfLights = 0;
		numOfCameras = 0;
	}
	
	virtual void SavetoFile(FILE *fp)
	{
		fwrite(&numOfObjects,sizeof(int),1,fp);
		for(int i=0; i<numOfObjects; i++)
		{
			pObject[i].SavetoFile(fp);
		}
		fwrite(&numOfMaterials,sizeof(int),1,fp);
		for(i=0; i<numOfMaterials; i++)
		{
			pMaterials[i].SavetoFile(fp);
		}
		fwrite(&numOfLights,sizeof(int),1,fp);
		for(i=0; i<numOfLights; i++)
		{
			pLights[i].SavetoFile(fp);
		}
		fwrite(&numOfCameras,sizeof(int),1,fp);
		for(i=0; i<numOfCameras; i++)
		{
			pCamera[i].SavetoFile(fp);
		}
	}
	
	virtual void LoadFromFile(FILE *fp)
	{
		fread(&numOfObjects,sizeof(int),1,fp);
		pObject.resize(numOfObjects);
		for(int i=0; i<numOfObjects; i++)
		{
			pObject[i].LoadFromFile(fp);
		}	
		fread(&numOfMaterials,sizeof(int),1,fp);
		pMaterials.resize(numOfMaterials);
		for(i=0; i<numOfMaterials; i++)
		{
			pMaterials[i].LoadFromFile(fp);
		}
		fread(&numOfLights,sizeof(int),1,fp);
		pLights.resize(numOfLights);
		for(i=0; i<numOfLights; i++)
		{
			pLights[i].LoadFromFile(fp);
		}
		fread(&numOfCameras,sizeof(int),1,fp);
		pCamera.resize(numOfCameras);
		for(i=0; i<numOfCameras; i++)
		{
			pCamera[i].LoadFromFile(fp);
		}
	}
	
	
	virtual bool LoadFromFile(char* filename)//以文件名读取模型
	{
		FILE *fp;
		fp = fopen(filename,"rb");
		if(fp == NULL) return false;

		LoadFromFile(fp);

		fclose(fp);
		
		return true;
	}
	
	
	//以下为相关预计算函数
	float cosAOB(float* a,float *b)//计算向量a，b夹角
	{
		return (a[0]*b[0]+a[1]*b[1]+a[2]*b[2])/
			sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2])/
			sqrt(b[0]*b[0]+b[1]*b[1]+b[2]*b[2]);
	}
	
	void sub(CVector3* c,CVector3* a,CVector3* b)
	{
		c->x = b->x - a->x;
		c->y = b->y - a->y;
		c->z = b->z - a->z;
	}
	
	//预计算光照
	float lightCoord(CVector3* v,CVector3* lightDir)
	{
		float tmpCoord = cosAOB(&v->x,&lightDir->x);
		return (tmpCoord+1.0f)/2.0f;
	}
	
	
	
	//预计算所有光照纹理坐标
	void calLightTex(CVector3* lightPos)
	{
		CVector3 tmp;
		for(int i = 0; i < numOfObjects ; i++)
			for(int j = 0; j < pObject[i].numOfFaces; j++)
			{
				for(int whichVertex = 2; whichVertex >= 0; whichVertex--)
				{
					int index = pObject[i].pFaces[j].vertIndex[whichVertex];	//顶点序号
					sub(&tmp,&pObject[i].pVerts[ index ],lightPos);
					//计算每个点的贴图坐标
					pObject[i].pNormals[ index ].x = lightCoord(&pObject[i].pNormals[ index ],&tmp);
				}
			}		
	}
	
	//计算缩放中的y值坐标
	float calY(float y,float clipt,float clipb,float scale)
	{
		if(y>clipt)//如果顶点在上剪切面上方（多数为安全气囊顶点）
			return y + (clipt-clipb) * (scale-1.0f);
		else//如果顶点在上剪切面下方（主副气囊分隔膜和安全气囊在该膜上的顶点）
			return clipb + (y - clipb)*scale;
	}

	void draw()
	{
		for (int k=0;k<numOfObjects;k++)
		{
			glPolygonMode(GL_FRONT_AND_BACK ,GL_FILL );
			int id = pObject[k].materialID;
			glBindTexture(GL_TEXTURE_2D,pMaterials[id].bindId);
			glBegin(GL_TRIANGLES);
			for (int j=0;j<pObject[k].numOfFaces;j++)
			{
				for (int ii=2;ii>=0;ii--)
				{
					CVector3 v;
					v = pObject[k].pVerts[pObject[k].pFaces[j].vertIndex[ii]];
					CVector3 n;
					n = pObject[k].pNormals[pObject[k].pFaces[j].normalIndex[ii]];
					glNormal3f(n.x,n.y,n.z);
					glVertex3f(v.x,v.y,v.z);
				}
			}
			glEnd();
		}
	}
};

#endif//#if !defined(AFX_T3DMODEL_H_INCLUDED_)
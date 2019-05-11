#if !defined(AFX_T3DMODEL_H_INCLUDED_)
#define AFX_T3DMODEL_H_INCLUDED_

/***************************************************************
���ļ����洢Ϊ��άģ���ļ���ʽ����༰�亯���ĵĶ���

**************************************************************/
#include "StdAfx.h"

// ��ά�����࣬���ڼ�¼����alphaͨ����RGBAɫ��
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

// ��ά�����࣬���ڼ�¼λ�ã���������RGB��ɫ
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
	
	void copy(CVector3* c)//������ά����
	{
		x = c->x;
		y = c->y;
		z = c->z;
	}
	
	void exchangeYZ()//�Ի�yz���꣬������max������ϵתΪOpenGL������ϵ
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

// ��ά�����࣬���ڼ�¼��������
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
�������еĶ�����Ϣ�������������飬�Ӵ���Ϣ����
��֪������Щ���㹹������Щ��
***********************************************************/
class tFace
{
public:
	int vertIndex[3];			// ��Ŷ�������
	int normalIndex[3];			// ��ŷ�������
	int coordIndex[3];			// �����������
	
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
Ϊʵ���������ã�����λͼ��
�Է�ѹ����ʽ��¼��ά�����rgbaλͼ
*******************************************************************/
class tInnerBitmap
{
public:
	
	int width;	//λͼ���
	int height;	//λͼ�߶�
	int aspect;	//�ݺ��
	unsigned char* pixel;//λͼ���д洢
	
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
�洢�������Ϣ�����п���ֻ��һЩ��ɫ��Ϣ��
*******************************************************************/
class tMaterialInfo
{
public:
	char  strName[255];			// The texture name
	char  strFile[255];			// The texture file name (If this is set it's a texture map)
//	BYTE  color[3];				// The color of the object (R, G, B)
	bool  bHasTexture;          //�������Ƿ���Texture(����ֻ����RGB��Ϣ)
	int   texureId;				// the texture ID
	unsigned int  bindId;
	CVector4	Ambient;			//�����ⷴ��ɫ
	CVector4	Diffuse;			//������ⷴ��ɫ
	CVector4	Specular;			//���淴��ⷴ��ɫ
	float		Shininess;			//����ָ��
	bool		SelfIllum;			//�����Ƿ񷢹�
	CVector4	Emission;			//���ʷ���ɫ

	float uTile;				// u tiling of texture  (Currently not used)
	float vTile;				// v tiling of texture	(Currently not used)
	float uOffset;			    // u offset of texture	(Currently not used)
	float vOffset;				// v offset of texture	(Currently not used)

	tInnerBitmap* ibmp;			//����λͼ
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
�洢ģ����ÿ���������Ϣ
***********************************************************************/
//ע�⣺��ֵʱҪ��pVerts��pFaces��pNormals����ռ�
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
	
	int	movement;				// ��̬���ԣ���������У�
	int* vertMovement;			// ���㶯̬���ԣ���������У�
	
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

		//��ʼ��
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
	
	//���°���һЩ����������غ���
	void normalize(CVector3* a)//��λ������
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
	
	void getDirection(CVector3* n,CVector3 a,CVector3 b)//���ba�ķ���
	{
		n->x = b.x - a.x;
		n->y = b.y - a.y;
		n->z = b.z - a.z;
	}
	
	void getPosition(CVector3 * tmp)//��ȡ�궨�þ��ε�����λ��
	{
		tmp->x = (pVerts[0].x + pVerts[1].x + pVerts[2].x + pVerts[3].x)/4.0f;
		tmp->y = (pVerts[0].y + pVerts[1].y + pVerts[2].y + pVerts[3].y)/4.0f;
		tmp->z = (pVerts[0].z + pVerts[1].z + pVerts[2].z + pVerts[3].z)/4.0f;
	}
	
	void getNormal(CVector3* tmpNor)//��ȡ�궨�þ��εķ��߷���
	{
		CVector3 tmpAB,tmpCB;//�洢�������ʱ����
		getDirection(&tmpAB,pVerts[1],pVerts[0]);
		getDirection(&tmpCB,pVerts[1],pVerts[2]);
		
		VectProduct(tmpNor,tmpCB,tmpAB);
		normalize(tmpNor);
	}
};


/***********************************************************************
�洢ģ����ÿ����Դ����Ϣ
***********************************************************************/
class tLight
{
public:
	char		strName[255];		//��Դ����

	CVector4	Position;			//��Դλ��
	CVector3	Direction;			//�۹ⷽ��

	float		Exponent;			//�۹�ָ��
	float		CutOff;				//������
	CVector3	Attenuation;		//˥�����ӣ�����Ϊ���������Լ���������

	CVector4	Ambient;			//���������ǿ��
	CVector4	Diffuse;			//����������ǿ��
	CVector4	Specular;			//���淴������ǿ��

	bool		LightOn;			//��Դ�Ƿ��

public:
	tLight()
	{
		//���¾���OpenGLĬ��ֵ��ʼ��
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
�洢ģ����ÿ���������Ϣ
***********************************************************************/
class tCamera
{
public:
	char		strName[255];		//�������

	CVector3	Position;			//��Դλ��
	CVector3	Direction;			//�۹ⷽ��

	float		NearPlane;			//��������	
	float		FarPlane;			//Զ������
	float		Fov;				//�ӽǻ���
		
	BOOL		IsOrtho;			//��;����

public:
	tCamera()
	{
		//��ʼ��
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
�洢����ģ���ļ�����Ϣ 
**********************************************************************************/
class t3DModel 
{
public:
	int numOfObjects;					// ģ���ļ��е���������
	vector<t3DObject> pObject;			// ģ���ļ��е������
	
	int numOfMaterials;                 // ģ���ļ��еĲ�������
	vector<tMaterialInfo> pMaterials;	// ģ���ļ��еĲ��ʱ�
	
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
	
	
	virtual bool LoadFromFile(char* filename)//���ļ�����ȡģ��
	{
		FILE *fp;
		fp = fopen(filename,"rb");
		if(fp == NULL) return false;

		LoadFromFile(fp);

		fclose(fp);
		
		return true;
	}
	
	
	//����Ϊ���Ԥ���㺯��
	float cosAOB(float* a,float *b)//��������a��b�н�
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
	
	//Ԥ�������
	float lightCoord(CVector3* v,CVector3* lightDir)
	{
		float tmpCoord = cosAOB(&v->x,&lightDir->x);
		return (tmpCoord+1.0f)/2.0f;
	}
	
	
	
	//Ԥ�������й�����������
	void calLightTex(CVector3* lightPos)
	{
		CVector3 tmp;
		for(int i = 0; i < numOfObjects ; i++)
			for(int j = 0; j < pObject[i].numOfFaces; j++)
			{
				for(int whichVertex = 2; whichVertex >= 0; whichVertex--)
				{
					int index = pObject[i].pFaces[j].vertIndex[whichVertex];	//�������
					sub(&tmp,&pObject[i].pVerts[ index ],lightPos);
					//����ÿ�������ͼ����
					pObject[i].pNormals[ index ].x = lightCoord(&pObject[i].pNormals[ index ],&tmp);
				}
			}		
	}
	
	//���������е�yֵ����
	float calY(float y,float clipt,float clipb,float scale)
	{
		if(y>clipt)//����������ϼ������Ϸ�������Ϊ��ȫ���Ҷ��㣩
			return y + (clipt-clipb) * (scale-1.0f);
		else//����������ϼ������·����������ҷָ�Ĥ�Ͱ�ȫ�����ڸ�Ĥ�ϵĶ��㣩
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
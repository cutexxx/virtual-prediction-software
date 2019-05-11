// Statium.cpp: implementation of the CStatium class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Statium.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace std;
static float min = 100;
static float max = -100;

string ReadStr(FILE *fp)
{
	char *s = new char[255];
	fgets(s,255,fp);
	std::string res = s;
	delete[] s;

	return res;
}

string FindString(FILE *fp,char *str)
{
	bool find= false;
	std::string line;

	while(!find)
	{
		if (feof(fp))
			return false;

		line = ReadStr(fp);
		int pos=line.find(str);
		if (pos>-1)
		{
			find = true;
			return line;
		}		
	}

	//impossible to get here!!
	return false;
}

CStatium::CStatium()
{
	m_bDrawAdsField = true;
	m_AdNeedToBeDraw = 0;
	m_bDrawBorder = true;
}

CStatium::~CStatium()
{

}

bool CStatium::Import(const char *filename)
{
	m_szBaseDir = filename;
	int pos = m_szBaseDir.ReverseFind('\\');
	m_szBaseDir = m_szBaseDir.Left(pos+1);

	FILE *fp;
	fp = fopen(filename,"rt");
	if (!fp)
		return false;

	//Init Texture
	ImportMaterial(fp);

	
	//Init Meshes
	ImportMeshes(fp);

	fclose(fp);

	adsTexture.Load("ad.bmp");

	return true;
}

bool CStatium::ImportMaterial(FILE *fp)
{
	int MatNum=0;
	std::string line;

	//读入 Materials 数
	line = FindString(fp,"Materials");
	sscanf(line.c_str(),"Materials = %d",&MatNum);

	//初始化所有Texture
	char *id = new char[10];
	char *fn = new char[20];
	for (int i=0;i<MatNum;i++)
	{
		if (feof(fp))
			return false;

		fscanf(fp,"%s %s",id,fn);
		std::string s1 = m_szBaseDir.GetBuffer(256);
		s1.append(fn,1,strlen(fn)-2);

		CTexture t;
		t.Load(s1.c_str());

		TextureMap.insert(pair<string,CTexture>(id,t));
	}

	delete[] id;
	delete[] fn;

	return true;
}


bool CStatium::ImportMeshes(FILE *fp)
{
	int MeshNum=0;
	std::string line;

	//读入 Meshes 数
	line = FindString(fp,"Meshes");
	sscanf(line.c_str(),"Meshes = %d",&MeshNum);

	for (int i=0;i<MeshNum;i++)
	{
		Mesh mesh;
		mesh.Import(fp);

		Meshes.push_back(mesh);
	}

	return true;
}

bool Mesh::Import(FILE *fp)
{
	int MeshNum = 0;
	string line;
	char *name=new char[20];

	//读入 subMesh 数
	line = FindString(fp,"Name");
	sscanf(line.c_str(),"Name = %s %d",name,&MeshNum);
	string subName;
	subName.append(string(name),1,strlen(name)-2);
	Name = subName;

	for (int i=0;i<MeshNum;i++)
	{
		SubMesh sm;
		sm.Import(subName,fp);

		SubMeshes.push_back(sm);
	}

	
	return true;
}

bool SubMesh::Import(string subName,FILE *fp)
{
	char *exName = new char[20];
	char *texture = new char[20];
	fscanf(fp,"%s %s",exName,texture);

	Name = subName + exName;
	Mat = texture;

	fscanf(fp,"%d",&VerNum);
	v = new Vertex[VerNum];

	//读入 顶点 数据
	for (int i=0;i<VerNum;i++)
	{
		v[i].Import(fp);
	}

	//读入 三角形 数据
	fscanf(fp,"%d",&TriNum);
	t = new Triangle[TriNum];
	for (int j=0;j<TriNum;j++)
	{
		t[j].Import(fp);
	}

	

	return true;
}

void Vertex::Import(FILE *fp)
{
	unsigned long color;
	fscanf(fp,"%f %f %f %f %f %x",&x,&y,&z,&u,&v,&color);

	uR = (color&0x00ff0000)>>16;
	uG = (color&0x0000ff00)>>8;
	uB = (color&0x000000ff);
	uA = (color&0xff000000)>>24;

	r = (float)uR/255.0;
	g = (float)uG/255.0;
	b = (float)uB/255.0;
	a = (float)uA/255.0;

	u = u;
	v = 1.0 - v;
}

void CStatium::Draw()
{
	glEnable(GL_TEXTURE_2D);
	for (int i=0;i<Meshes.size();i++)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		//绘制不透明物体
		glEnable(GL_ALPHA_TEST);
		//只有不透明像素可以通过，即绘制的像素alpha>=1.0
		glAlphaFunc(GL_EQUAL,1.0f);
		if (Meshes[i].Name.compare("SKY")==0)
		{
			//			continue;
			glPushMatrix();
			glScalef(10,10,10);
		}
		glDisable(GL_BLEND);
		int j;
		for (j=0;j<Meshes[i].SubMeshes.size();j++)
		{
			SubMesh *subMesh = &Meshes[i].SubMeshes[j];
			map<string,CTexture>::iterator iter;
			iter = TextureMap.find(subMesh->Mat);
			iter->second.Bind();

			for (int k=0;k<subMesh->TriNum;k++)
			{
				int a,b,c;
				a = subMesh->t[k].v[0];
				b = subMesh->t[k].v[1];
				c = subMesh->t[k].v[2];
				glBegin(GL_TRIANGLES);
					glTexCoord2f(subMesh->v[a].u,subMesh->v[a].v);
					glColor4f(subMesh->v[a].r,subMesh->v[a].g,subMesh->v[a].b,subMesh->v[a].a);
					glVertex3f(subMesh->v[a].x,subMesh->v[a].y,subMesh->v[a].z);

					glTexCoord2f(subMesh->v[c].u,subMesh->v[c].v);
					glColor4f(subMesh->v[c].r,subMesh->v[c].g,subMesh->v[c].b,subMesh->v[c].a);
					glVertex3f(subMesh->v[c].x,subMesh->v[c].y,subMesh->v[c].z);

					glTexCoord2f(subMesh->v[b].u,subMesh->v[b].v);
					glColor4f(subMesh->v[b].r,subMesh->v[b].g,subMesh->v[b].b,subMesh->v[b].a);
					glVertex3f(subMesh->v[b].x,subMesh->v[b].y,subMesh->v[b].z);
				glEnd();
			}
		}

		//第二次，绘制透明物体，打开深度检测，关闭深度缓存写入
		glDisable(GL_ALPHA_TEST);
		glAlphaFunc(GL_ALWAYS,1.0);
		glEnable(GL_BLEND);					// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);			// Set The Blending Function For Translucency
		glDepthMask(false);
		glEnable(GL_DEPTH_TEST);
	
		if (Meshes[i].Name.compare("FIELD2")==0)
		{
			//			continue;
			glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
			glDepthMask(0);
		}
		
		if (Meshes[i].Name.compare("FIELD3")==0)
		{
			//			continue;
			glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
			glDepthMask(0);
		}

		for (j=0;j<Meshes[i].SubMeshes.size();j++)
		{
			SubMesh *subMesh = &Meshes[i].SubMeshes[j];
			map<string,CTexture>::iterator iter;
			iter = TextureMap.find(subMesh->Mat);
			iter->second.Bind();
			
			for (int k=0;k<subMesh->TriNum;k++)
			{
				int a,b,c;
				a = subMesh->t[k].v[0];
				b = subMesh->t[k].v[1];
				c = subMesh->t[k].v[2];
				glBegin(GL_TRIANGLES);
				glTexCoord2f(subMesh->v[a].u,subMesh->v[a].v);
				glColor4f(subMesh->v[a].r,subMesh->v[a].g,subMesh->v[a].b,subMesh->v[a].a);
				glVertex3f(subMesh->v[a].x,subMesh->v[a].y,subMesh->v[a].z);
				
				glTexCoord2f(subMesh->v[c].u,subMesh->v[c].v);
				glColor4f(subMesh->v[c].r,subMesh->v[c].g,subMesh->v[c].b,subMesh->v[c].a);
				glVertex3f(subMesh->v[c].x,subMesh->v[c].y,subMesh->v[c].z);
				
				glTexCoord2f(subMesh->v[b].u,subMesh->v[b].v);
				glColor4f(subMesh->v[b].r,subMesh->v[b].g,subMesh->v[b].b,subMesh->v[b].a);
				glVertex3f(subMesh->v[b].x,subMesh->v[b].y,subMesh->v[b].z);
				glEnd();
			}
		}
		glDepthMask(true);

		if (Meshes[i].Name.compare("SKY")==0)
		{
			glPopMatrix();
		}
	}


	if (m_bDrawAdsField)
	{
		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_COLOR);
		glColor4f(1.0,1.0,1.0,1.0);
		for (int i=0;i<Ads.size();i++)
		{
			DrawAds(i);
		}
		if (m_AdNeedToBeDraw<Ads.size())
		{
			glEnable(GL_COLOR);
			glColor4f(0.0,1.0,0.0,1.0);
			DrawAds(m_AdNeedToBeDraw);
			glColor4f(1,1,1,1);
			if (m_bDrawBorder)
			{
				DrawAdBorder(m_AdNeedToBeDraw);
			}
		}
	}
}

void Triangle::Import(FILE *fp)
{
	fscanf(fp,"%d %d %d",&v[0],&v[1],&v[2]);
}


void CStatium::ImportAds(const char *filename)
{
	FILE *fp;
	fp = fopen(filename,"rt");
	if (fp)
	{
		int NumOfFaces;
		float x,y,z;
		int mat;
		float rot;
		fscanf(fp,"%d\n",&NumOfFaces);
		for (int i=0;i<NumOfFaces;i++)
		{
			Ad ad;
			fscanf(fp,"%f %f %f\n",&x,&y,&z);
			ad.v[0].x = x;
			ad.v[0].y = y;
			ad.v[0].z = z;
			fscanf(fp,"%f %f %f\n",&x,&y,&z);
			ad.v[1].x = x;
			ad.v[1].y = y;
			ad.v[1].z = z;
			fscanf(fp,"%f %f %f\n",&x,&y,&z);
			ad.v[2].x = x;
			ad.v[2].y = y;
			ad.v[2].z = z;
			fscanf(fp,"%f %f %f\n",&x,&y,&z);
			ad.v[3].x = x;
			ad.v[3].y = y;
			ad.v[3].z = z;

			fscanf(fp,"%d %f\n",&mat,&rot);

			ad.mat = mat;
			ad.rot = rot;

			Ads.push_back(ad);
		}
		fclose(fp);
	}
}

void CStatium::DrawAds(int i)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	adsTexture.Bind();
	float ymax = 1.0-(float)Ads[i].mat*1.0f/8.0f;
	float ymin = ymax - 1.0/8.0f;

	glPushMatrix();

	float cx,cy;
	cx = (Ads[i].v[0].x + Ads[i].v[2].x)/2.0;
	cy = (Ads[i].v[0].y + Ads[i].v[2].y)/2.0;

	glTranslatef(cx,cy,0);
	glRotatef(Ads[i].rot,0,0,1);
	glTranslatef(-cx,-cy,0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK );

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0,ymax);
	glVertex3f(Ads[i].v[0].x,Ads[i].v[0].y,Ads[i].v[0].z);
	glTexCoord2f(0.0,ymin);
	glVertex3f(Ads[i].v[1].x,Ads[i].v[1].y,Ads[i].v[1].z);
	glTexCoord2f(1.0,ymin);
	glVertex3f(Ads[i].v[2].x,Ads[i].v[2].y,Ads[i].v[2].z);
	glEnd();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0,ymax);
	glVertex3f(Ads[i].v[0].x,Ads[i].v[0].y,Ads[i].v[0].z);
	glTexCoord2f(1.0,ymin);
	glVertex3f(Ads[i].v[2].x,Ads[i].v[2].y,Ads[i].v[2].z);
	glTexCoord2f(1.0,ymax);
	glVertex3f(Ads[i].v[3].x,Ads[i].v[3].y,Ads[i].v[3].z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(1.0,ymax);
	glVertex3f(Ads[i].v[0].x,Ads[i].v[0].y,Ads[i].v[0].z);
	glTexCoord2f(0.0,ymin);
	glVertex3f(Ads[i].v[2].x,Ads[i].v[2].y,Ads[i].v[2].z);
	glTexCoord2f(1.0,ymin);
	glVertex3f(Ads[i].v[1].x,Ads[i].v[1].y,Ads[i].v[1].z);
	glEnd();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(1.0,ymax);
	glVertex3f(Ads[i].v[0].x,Ads[i].v[0].y,Ads[i].v[0].z);
	glTexCoord2f(0.0,ymax);
	glVertex3f(Ads[i].v[3].x,Ads[i].v[3].y,Ads[i].v[3].z);
	glTexCoord2f(0.0,ymin);
	glVertex3f(Ads[i].v[2].x,Ads[i].v[2].y,Ads[i].v[2].z);
	glEnd();

	glPopMatrix();

	glDisable(GL_CULL_FACE);
}


// Function name	: CStatium::ExportAds
// Description	    : 保存修改后的广告
// Return type		: void 
// Argument         : const char *filename
void CStatium::ExportAds(const char *filename)
{
	FILE *fp;
	fp = fopen(filename,"wt");
	fprintf(fp,"%d\n",Ads.size());
	for (int i=0;i<Ads.size();i++)
	{
		fprintf(fp,"%f %f %f\n",Ads[i].v[0].x,Ads[i].v[0].y,Ads[i].v[0].z);
		fprintf(fp,"%f %f %f\n",Ads[i].v[1].x,Ads[i].v[1].y,Ads[i].v[1].z);
		fprintf(fp,"%f %f %f\n",Ads[i].v[2].x,Ads[i].v[2].y,Ads[i].v[2].z);
		fprintf(fp,"%f %f %f\n",Ads[i].v[3].x,Ads[i].v[3].y,Ads[i].v[3].z);
		fprintf(fp,"%d %f\n",Ads[i].mat,Ads[i].rot);
	}
}

void CStatium::DrawAdBorder(int i)
{
	static bool flash = true;
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	float ymax = 1.0-(float)Ads[i].mat*1.0f/8.0f;
	float ymin = ymax - 1.0/8.0f;
	
	glPushMatrix();
	
	float cx,cy;
	cx = (Ads[i].v[0].x + Ads[i].v[2].x)/2.0;
	cy = (Ads[i].v[0].y + Ads[i].v[2].y)/2.0;
	
	glTranslatef(cx,cy,0);
	glRotatef(Ads[i].rot,0,0,1);
	glTranslatef(-cx,-cy,0);

	glLineWidth(5);
	if (flash)
	{
		glColor3f(1,1,1);
	}
	else
	{
		glColor3f(0,0,1);
	}
	flash = !flash;

	glBegin(GL_LINE_LOOP);
	glVertex3f(Ads[i].v[0].x,Ads[i].v[0].y,Ads[i].v[0].z);
	glVertex3f(Ads[i].v[1].x,Ads[i].v[1].y,Ads[i].v[1].z);
	glVertex3f(Ads[i].v[2].x,Ads[i].v[2].y,Ads[i].v[2].z);
	glVertex3f(Ads[i].v[3].x,Ads[i].v[3].y,Ads[i].v[3].z);
	glEnd();
	glLineWidth(1);

	glPopMatrix();
}

void CStatium::DrawSelectAds()
{
	for (int i=0;i<Ads.size();i++)
	{
		glLoadName(i);
		DrawAds(i);
	}
}

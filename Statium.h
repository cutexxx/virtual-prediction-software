// Statium.h: interface for the CStatium class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATIUM_H__D6C3CDE2_09E2_438B_99ED_3EE1B772062A__INCLUDED_)
#define AFX_STATIUM_H__D6C3CDE2_09E2_438B_99ED_3EE1B772062A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable:4786)

#include <vector>
#include <string>
#include <map>

#include "Texture.h"
#include "Camera.h"

using namespace std;

struct Vertex
{
	float x,y,z,u,v;
	float r,g,b,a;
	unsigned char uR,uG,uB,uA;
public:
	void Import(FILE *fp);
};

struct Triangle
{
	unsigned int v[3];
public:
	void Import(FILE *fp);
};

class SubMesh
{
public:
	bool Import(string subName,FILE *fp);
	string			Name;		//名称
	string			Mat;		//纹理
	unsigned int	VerNum;		//顶点数
	unsigned int	TriNum;		//三角形数
	Vertex			*v;			//顶点列表
	Triangle		*t;			//三角形列表
};

class Mesh
{
public:
	bool Import(FILE *fp);
	string Name;				//名称
	unsigned short Num;			//Meshes中的物体数量
	std::vector<SubMesh> SubMeshes;		//子物体列表

};

struct Ad
{
	Vertex v[4];
	int mat;
	float rot;
};

class CStatium  
{
public:
	bool m_bDrawBorder;
	void DrawSelectAds();
	void DrawAdBorder(int i);
	void ExportAds(const char *filename);
	int m_AdNeedToBeDraw;
	void DrawAds(int i);
	bool m_bDrawAdsField;
	void ImportAds(const char *filename);
	//计算第i个广告牌的画面比例
	CString m_szBaseDir;
	void Draw();
	///导入.sef体育场模型文件
	bool Import(const char *filename);
	CStatium();
	virtual ~CStatium();
	std::map<std::string,CTexture> TextureMap;			//纹理
	std::vector<Ad> Ads;			//广告列表	
private:
	std::vector<Mesh> Meshes;			//物体列表	
	CTexture adsTexture;
	

	bool ImportMeshes(FILE *fp);
	bool ImportMaterial(FILE *fp);
};

#endif // !defined(AFX_STATIUM_H__D6C3CDE2_09E2_438B_99ED_3EE1B772062A__INCLUDED_)

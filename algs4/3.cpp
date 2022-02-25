#include "windows.h" 
#include<bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

//��Ȩ����ߵ���������
class DirectedEdge {
private:
	int v;//�ߵ����
	int w;//�յ�
	double weight;//�ߵ�Ȩ��

public:
	DirectedEdge(int v=0, int w=0, double weight=-1) {
		this->v = v;
		this->w = w;
		this->weight = weight;
	}
	void initDirectedEdge(int v, int w, double weight = -1) {
		this->v = v;
		this->w = w;
		this->weight = weight;
	}
	double getweight() {return weight;}
	int from() {return v;}
	int to() { return w; }
	string toString() {  //������ַ�����ʾ
		string s = to_string(v)+"->"+to_string(w)+":"+to_string(weight);
		return s;
	}
};
//��Ȩ����ͼ����������
class EdgeWeightedDigraph {
private:
	int V;//��������
	int E;//������
	vector<vector<DirectedEdge> > adj;//�ڽӱ�

public:
	EdgeWeightedDigraph(int V) {  //����v������Ŀ�����ͼ
		this->V = V;
		this->E = 0;
		adj.resize(V);
	}
	//EdgeWeightedDigraph(In in)//���������ж�ȡͼ�Ĺ��캯��
	int getV() { return V; }
	int getE() { return E; }
	void addEdge(DirectedEdge e) {
		adj[e.from()].push_back(e);//�ҵ������ߵ���㲢��ӵ��ڽӱ���
		E++;//������+1
	}
	vector<DirectedEdge>* getadj(int v) {//���ش�vָ�������б�,����ʱע��ʹ������
		vector<DirectedEdge>* adjIter = &adj[v];
		return adjIter;
	}
	vector<DirectedEdge>* edges() {//����ͼ�����б�
		vector<DirectedEdge> *bag = new vector<DirectedEdge>;
		for (int v = 0; v < V; v++) {
			for (auto i = adj[v].begin(); i != adj[v].end(); i++)
				bag->push_back(*i);
		}
		return bag;
	}
};

//�����������
class Point {
private:
	int n;//���
	int x;//x��y����
	int y;
public:
	Point(int N = 0, int X = 0, int Y = 0) :n(N), x(X), y(Y) {}
	void initPoint(int N, int X, int Y) {
		this->n = N;
		this->x = X;
		this->y = Y;
	}
	int getX() { return x; }
	int getY() { return y; }
	static double calWeight(Point& p1, Point& p2) {//���������ŷ�Ͼ��뼴Ȩ��
		return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	}
	void show() { cout << n << ":" << x << "," << y << endl; }
};

//���ȶ��е�ʵ��
template<class Key>
class IndexMinPQ {
private:
	int N;//PQ�е�Ԫ������
	int* pq;//���������,��1��ʼ
	int* qp;//����:qp[pq[i]] = pq[qp[i]] = i
	Key* keys;//�����ȼ�֮�ֵ�Ԫ��
	bool less(int i, int j) {
		int ki = pq[i];
		int kj = pq[j];
		return keys[ki] > keys[kj];
	}
	void exch(int i, int j) {
		int t = pq[i]; pq[i] = pq[j]; pq[j] = t;
		int qpi = pq[i];
		int qpj = pq[j];
		qp[qpi] = i;
		qp[qpj] = j;
	}
	void swim(int k) {
		while (k > 1 && less(k / 2, k)) {
			exch(k / 2, k);
			k = k / 2;
		}
	}
	void sink(int k) {
		while (2 * k <= N) {
			int j = 2 * k;
			if (j < N && less(j, j + 1))j++;
			if (!less(k, j))break;
			exch(k, j);
			k = j;
		}
	}
public:
	IndexMinPQ(int maxN) {
		N = 0;
		keys = new Key[maxN + 1];
		pq = new int[maxN + 1];
		qp = new int[maxN + 1];
		for (int i = 0; i <= maxN; i++) {
			qp[i] = -1;
		}
	}
	~IndexMinPQ() { delete pq, qp, keys; }
	bool isEmpty() { return N == 0; }
	void toEmpty() { N = 0; }
	bool contains(int k) { return qp[k] != -1; }//�Ƿ��������Ϊk ��Ԫ��
	void insert(int k, Key key) {//����һ��Ԫ��,����������k�����
		N++;
		qp[k] = N;
		pq[N] = k;
		keys[k] = key;
		swim(N);
	}
	void change(int k, Key key) {//������k ��Ԫ����Ϊkey
		keys[k] = key;
		swim(qp[k]);
		sink(qp[k]);
	}
	int delMin() {//ɾ����СԪ�ز�������������
		int indexOfMin = pq[1];
		exch(1, N--);
		sink(1);
		keys[pq[N + 1]] = NULL;
		qp[pq[N + 1]] = -1;
		return indexOfMin;
	}
	Key getMin() { //������СԪ��
		return keys[pq[1]];
	}


};
//�Ա����ҹ��ı߸�����ɫ
void DrawLine(int p1, int p2, Point* P) {
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(10.0);
	glVertex2f(P[p1].getX(), P[p1].getY());
	glVertex2f(P[p2].getX(), P[p2].getY());
	glEnd();
	glFlush();    //�Ƿ�ʱ����ʾɨ�������·
	Sleep(0.1);
}
//�������·��
class DijkstraSP {
private:
	DirectedEdge* edgeTo;
	double* distTo;
	double* DistTo;
	IndexMinPQ<double>* pq;//���ȶ���
	
	void relax(EdgeWeightedDigraph* G, int v,int end, Point* P){//������ɳ�
		vector<DirectedEdge>* E = G->getadj(v);
		for (auto e = E->begin(); e != E->end(); e++) {
			
			int w = e->to();
			DrawLine(e->from(),w, P);
			if (DistTo[w] > DistTo[v]-Point::calWeight(P[v], P[end]) + e->getweight()+ Point::calWeight(P[w], P[end])) {
			//if (distTo[w] > distTo[v] + e->getweight()) { //�ڶ��ָĽ���ʽ
				DistTo[w] = DistTo[v] - Point::calWeight(P[v], P[end]) + e->getweight() + Point::calWeight(P[w], P[end]);
				distTo[w] = distTo[v] + e->getweight();
				edgeTo[w] = *e;
				if (pq->contains(w))
					//pq->change(w, distTo[w]);
					pq->change(w, DistTo[w]);
				else
					//pq->insert(w, distTo[w]);
					pq->insert(w, DistTo[w]);
			}
			if (w == end) {//����Ŀ�ĵؾ�ֹͣ����
				pq->toEmpty();
				return;
			}
		}
	}

public:
	DijkstraSP(EdgeWeightedDigraph *G,int s,int end, Point* P) {//G:����ͼ  s:��ʼ��
		clock_t start, to;//��¼ʱ��
		start = clock();
		edgeTo = new DirectedEdge[G->getV()];//s��v�����·���ϵ����һ����
		distTo = new double[G->getV()];//dist[w]�Ǵ�s��w�����·���ĳ���
		DistTo = new double[G->getV()];//DistTo = distTo+distant(v,t),���ϵ��յ��ֱ�߾���
		pq = new IndexMinPQ<double>(G->getV());
		for (int v = 0; v < G->getV(); v++) {
			distTo[v] = DBL_MAX;//��ʼ���������ֵ
			DistTo[v] = DBL_MAX;//��ʼ���������ֵ
		}
		distTo[s] = 0.0;
		DistTo[s] = distTo[s]+Point::calWeight(P[s],P[end]);
		pq->insert(s, 0.0);
		to = clock();
		cout << "time = " << double(to - start) / CLOCKS_PER_SEC << "s" << endl;
		while (!pq->isEmpty()) {
			relax(G, pq->delMin(),end,P);
		}
	}
	~DijkstraSP() {
		delete edgeTo, distTo, pq,DistTo;
	}
	double getDistTo(int v) {return distTo[v];}
	bool hasPathTo(int v) { return distTo[v] < DBL_MAX; }
	vector<DirectedEdge>* pathTo(int v) {//���ص���һ�������vector
		if (!hasPathTo(v))return NULL;
		vector<DirectedEdge> *path = new vector<DirectedEdge>();
		for (DirectedEdge e = edgeTo[v]; e.getweight() != -1; e = edgeTo[e.from()]) {
			path->insert(path->begin(),e);
		}
		return path;
	}
};


//��ͼ��� ���ڴ�С�ı�ʱ
void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1000, 13000.0, -1000.0 * (GLfloat)h / (GLfloat)w, 6187.5 * (GLfloat)h / (GLfloat)w, -50.0, 50.0);
	else
		glOrtho(-1000 * (GLfloat)h / (GLfloat)w, 13000.0 * (GLfloat)h / (GLfloat)w, -1000.0, 6187.5, -50.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//�������б�
void DrawEdges(vector<DirectedEdge> *de, Point *P) {
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 1.0);
	for (auto i = de->begin(); i != de->end(); i++) {
		glVertex2f(P[i->from()].getX(), P[i->from()].getY());
		glVertex2f(P[i->to()].getX(), P[i->to()].getY());
	}
	glEnd();
}
//�����·�����
void DrawPaths(vector<DirectedEdge>* de, Point* P) {
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(10.0);
	for (auto i = de->begin(); i != de->end(); i++) {
		glVertex2f(P[i->from()].getX(), P[i->from()].getY());
		glVertex2f(P[i->to()].getX(), P[i->to()].getY());
	}
	glEnd();
}

//������������(��ΪRenderSceneû������)
void RenderScene()
{   
	ifstream infile;
	infile.open("D://Codes/C/3Map.txt", ios::in);
	int V, E;//����ͱߵ�����
	infile >> V >> E;
	//cout << V << E;
	//��������ͼ
	EdgeWeightedDigraph* G = new EdgeWeightedDigraph(V);
	Point* P = new Point[V];
	int N, X, Y;
	for (int i = 0; i < V; i++) {
		infile >> N >> X >> Y;
		//cout << N << X << Y;
		P[i].initPoint(N, X, Y);//��õ�����
	}
	//��ñ�����
	int v, w;
	for (int i = 0; i < E; i++) {
		infile >> v >> w;
		double weight = Point::calWeight(P[v], P[w]);
		DirectedEdge* e = new DirectedEdge(v, w,weight);
		//cout << v << ' ' << w << endl;
		G->addEdge(*e);
		e = new DirectedEdge(w, v, weight);
		G->addEdge(*e);
		delete e;
	}
	
	int from, to;//��¼�����յ�
	while (true) {
		cout << "please input from and to: ";
		cin >> from >> to;
		cout << endl;
		
		//�˳�����
		if (from == -1 && to == -1)
			exit(0);

		//����ȫ��·��
		vector<DirectedEdge>* de = new vector<DirectedEdge>;
		de = G->edges();
		glClear(GL_COLOR_BUFFER_BIT);
		DrawEdges(de, P);
		glFlush();
		clock_t start, end;//��¼ʱ��
		start = clock();
		//�ҵ����·����ӡ������
		DijkstraSP* Dij = new DijkstraSP(G, from, to, P);//���
		vector<DirectedEdge>* result = Dij->pathTo(to);//�յ�
		end = clock();

		if (result != NULL) {
			DrawPaths(result, P);
			for (auto i = result->begin(); i != result->end(); i++) {
				cout << i->toString() << endl;
			}
			cout << "distant= "<<Dij->getDistTo(to)<< endl;
			cout << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
		}
		else {
			cout << "There is no shortest path from " << from << " to " << to << endl;
			cout << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
		}

		glFlush();
		/*
		for (int i = 0; i < 10; i++) {
			P[i].show();
		}*/
		delete Dij;
	}
	delete G, P;
}

int main(int argc, char* argv[]) {
	//��ͼ
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1100, 900);
	glutInitWindowPosition(500, 100);

	glutCreateWindow("Map");
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);  //���ڴ�С�ı�ʱ

	/*���ȶ��в���
	IndexMinPQ<double> pq(10);
	pq.insert(1, 0.0);
	pq.insert(2, 1.0);
	cout << pq.isEmpty() << endl;
	cout << pq.delMin() << endl;
	cout << pq.delMin() << endl;
	cout << pq.contains(2) << endl;
	*/
	glutMainLoop();
	
	//for (auto i = de->begin(); i != de->end(); i++)
		//cout << (i->toString()) << endl;
	return 0;
}
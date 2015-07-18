#include "MyGraph.h"
MyGraph::MyGraph(){
}
MyGraph::MyGraph(int n) {
	for (int i = 0; i <n; i++) {
		for (int j = 0; j <n; j++) {
			this->_matrix[i][j] = 0;
		}
	}
}
MyGraph::MyGraph(string filename, char type, char typeH){
	ifstream input(filename);
	if (!input) cout << "File Error!";
	input >> this->_n;
	for (int i = 0; i < this->_n; i++){
		for (int j = 0; j < this->_n; j++){
			this->_matrix[i][j] = 0;
		}
	}
	if (type == 'D'){
		while (!input.eof()){
			int x, y,data;
			input >> x >> y>>data;
			this->_matrix[x - 1][y - 1] = data;
			if (typeH == 'N'){
				this->_matrix[y - 1][x - 1] = data;
			}
		}
	}
	if (type == 'M'){
		for (int i = 0; i < _n; i++){
			for (int j = 0; j < _n; j++){
				input >> this->_matrix[i][j];
			}
		}
	}
	if (type != 'M'&&type != 'D')cout << "Dont understand type graphic!";
	input.clear();
	input.close();
}
//-------------------------------//
void MyGraph::setEdge(int x, int y, char typeH,int oma){
	if (x - 1 >= 0 && y - 1 <= _n - 1){
		this->_matrix[x - 1][y - 1] = oma;
		if (typeH == 'N')this->_matrix[y - 1][x - 1] = oma;

	}
	else{
		cout << "Do not exist the edge!";
	}
}
void MyGraph::setNode(int x){
	this->_n++;
	for (int i = 0; i < this->_n; i++)
	{
		this->_matrix[this->_n - 1][i] = 0;
		this->_matrix[i][this->_n - 1] = 0;
	}
}
//------------------------------//
int MyGraph::getRank(int x)const{
	int count = 0;
	for (int i = 0; i < this->_n; i++){
		if (this->_matrix[x][i] != 0)count++;
	}
	return count;
}
//-----------------------------//
void MyGraph::DFSmain(bool *checknode, Stack<int>&road, int x, int y, bool &finish)const{
	checknode[x] = true;
	
	if (x == y||finish){
		finish = true;
		return;
	}
	for (int i = 0; i <this->_n; i++){
		if (_matrix[x][i] != 0 && !checknode[i]&&!finish){
			road.Push(i + 1);
			DFSmain(checknode, road, i,y,finish);
		}
	}
	if (x != y&&!finish) road.Pop();
}
List<int> MyGraph::DFS(int x, int y)
{
	/*check node: if checknode is true then node was browsing
	if checknode is false then node did not browsing*/
	bool *checknode = new bool[this->_n];
	Stack<int> road;
	List<int> newroad;
	for (int i = 0; i < this->_n; i++){
		checknode[i] = false;
	}
	bool finish = false;
	road.Push(x);
	DFSmain(checknode, road, x - 1, y - 1,finish);
	while (!road.getNULL())
	{
		newroad.AddL(road.Pop());
	}
	//newroad = road;
	return newroad;
}
//------------------------------//
List<int> MyGraph::BFS(int x,int y){
	bool *checknode = new bool[this->_n];
	for (int i = 0; i < this->_n; i++){
		checknode[i] = false;
	}
	
	List<int> road;
	for (int i = 0; i < this->_n; i++){
		road.AddF(-2);
	}
	List<int> newroad;
	bool check=BFSmain(checknode, road, x-1,y-1);
	if (check) 
	{
		int r_road = y - 1;
		while (true) 
		{
			newroad.AddF(r_road + 1);
			r_road = road.Value(r_road);
			if (r_road == -1) break;
		}
	}
	else
	{
		cout << "Not direction! from "<<x<<" to "<<y<<".";//ducthang
	}
	return newroad;
}
bool MyGraph::BFSmain(bool *checknode, List<int>&road, int x,int y)const {
	QueueList<int> node;
	if (x >= this->_n||y>=this->_n)return false;
	node.ADD(x);
	road.Fix(x, -1);
	checknode[x] = true;
	while (!node.empty()){
		x = node.GET();
		for (int i = 0; i < this->_n; i++){
			if (this->_matrix[x][i] != 0 && !checknode[i]){
				checknode[i] = true;
				node.ADD(i);
				road.Fix(i,x);
				if (i == y)return true;
			}
			
		}
	}
	return false;
}
//------------------------------//
List<int> MyGraph::Euler(){
	int booler = Review();
	bool kt = false;
	List<int>road;
	if (booler == -1){
		
		int l = 0;
		while(l <this->_n){
			int matrix[100][100];
			for (int i = 0; i < this->_n; i++)
				for (int j = 0; j < this->_n; j++)
					matrix[i][j] = this->_matrix[i][j];
			road.Delete();
			kt = false;
			Search_Euler(matrix, l, road, kt);
			if (road.Value(road.Length() - 1) == -1){
				road.Delete(road.Length() - 1);
				break;
			}
			l++;
		}
		
	}
	else{
		if (booler == -2){
			cout << "Impossible!";
		}
		else{
			int matrix[100][100];
			for (int i = 0; i < this->_n; i++)
				for (int j = 0; j < this->_n; j++)
					matrix[i][j] = this->_matrix[i][j];
			Search_Euler(matrix, booler-1, road,kt);
			if (road.Value(road.Length() - 1) == -1) road.Delete(road.Length() - 1);
		}
	}
	return road;
}
void MyGraph::Search_Euler(int matrix[][100], int x, List<int>&road, bool &kt){
	road.AddL(x+1);
	for (int i = 0; i < this->_n; i++){
		if (matrix[x][i] != 0){
			matrix[x][i] = 0;
			matrix[i][x] = 0;
			Search_Euler(matrix, i, road,kt);
		}
	}
	if (kt == false){
		kt = true;
		road.AddL(-1);
	}
}
int MyGraph::Review()const{
	int Count_Odd = 0,save_note;
	for (int i = 0; i < this->_n; i++){
		if (getRank(i) % 2 != 0){
			Count_Odd++;
			save_note = i;
		}
	}
	if (Count_Odd == 0)return -1;
	if (Count_Odd == 2)return save_note;
	return -2;
}
//------------------------------//
bool check = false;
List<List<int>>  MyGraph::Hamilton()
{
	List<List<int>> road;
	if (Connectivity())
	{
		bool *checknode = new bool[this->_n];
		for (int i = 0; i < this->_n; i++) checknode[i] = false;
		Stack<int> _stack;
		int start = 0;
		
		for (int i = 0; i < this->_n; i++)
		{
			start = i;
			check = false;
			Try(i, checknode, start, _stack, road);
		}
	}
	return road;
}

void MyGraph::Try(int n,bool *checknode,int &start,Stack<int> _stack,List<List<int>> &road)
{
	if (n == start && check)
	{
		for (int i = 0; i < this->_n; i++)
		{
			if (!checknode[i]) return;
		}
		_stack.Push(n + 1);
		List<int> ra;
		Stack<int> ka = _stack;
		while (!ka.getNULL()) ra.AddL(ka.Pop());
		road.AddL(ra);
		_stack.Pop();

	}
	check = true;
	for (int i = 0; i < this->_n; i++)
	{
		
		if (!checknode[i] && (int)this->_matrix[n][i] != 0)
		{
			checknode[i] = true;
			_stack.Push(n + 1);
			Try(i, checknode, start, _stack, road);
			checknode[i] = false;
			_stack.Pop();
		}
	}
	
}
//------------------------------//
void MyGraph::GraphicOut()const{
	for (int i = 0; i < this->_n; i++){
		for (int j = 0; j < this->_n; j++){
			cout << this->_matrix[i][j] << " ";
		}
		cout << endl;
	}
}
//------------------------------//
List<int> MyGraph::Dijkstra(int x, int y)const{
	int start = x;
	x = x - 1; y = y - 1;
	bool *checknode = new bool[this->_n];
	List<int> road;
	int *sum = new int[this->_n];
	int *roadsum = new int[this->_n];
	for (int i = 0; i < this->_n; i++) {
		sum[i] = -1;
		roadsum[i] = -2;
		checknode[i] = false;
	}
	sum[x] = 0;
	int k = 0;
	int min = 0;
	while (true){
		if (checknode[x] || x == y)break;
		//cout << endl;
		checknode[x] = true;
		min = 0;
		for (int i = 0; i < this->_n; i++){
			if (this->_matrix[x][i] != 0 && !checknode[i]){
				if (sum[x] + this->_matrix[x][i] < sum[i] || sum[i] == -1){
					sum[i] = sum[x] + this->_matrix[x][i];
					roadsum[i] = x;
				}
			}
			if ((sum[i] < min || min == 0) && !checknode[i] && sum[i]>0){
				min = sum[i];
				k = i;
			}
			//cout << " " << sum[i] <<"("<< roadsum[i]+1<<")";
		}
		x = k;
		//cout << endl;
		/*int min = 0;
		for (int i = 0; i < this->_n; i++){

			if ((sum[i] < min || min == 0) && !checknode[i] && sum[i]>0){
				min = sum[i];
				x = i;
			}
		}*/
	}
	x = y;
	while (true){
		if (x < 0) {
			road.Delete();
			break;
		}
		road.AddF(x + 1);
		if (x == start - 1)break;
		x = roadsum[x];
	}
	return road;
}
//------------------------------//
MyGraph::~MyGraph(){

}
//-----------------------------//
List<PHI<int>> MyGraph::coloring()const {
	List<PHI<int>> colors;
	int *node = new int[this->_n];
	bool *checknode = new bool[this->_n];
	for (int i = 0; i < this->_n; i++)
	{
		node[i] = i;
		checknode[i] = false;
	}
	for (int i = 0; i < this->_n; i++) {
		for (int j = i + 1; j < this->_n; j++) {
			if (getRank(node[i]) < getRank(node[j])) {
				int temp = node[i];
				node[i] = node[j];
				node[j] = temp;
			}
		}
	}
	
	char *a = new char[this->_n];
// check coloring 
	for (int i = 0; i < this->_n; i++)
	{
		int k = node[i];
		char *arrays = new char[this->_n];
		int count = 0;
		for (int j = 0; j < this->_n; j++)
		{
			if (checknode[j] && this->_matrix[k][j] != 0)
			{
				arrays[count++] = a[j];
			}
		}
		int color = (int)'A';
		for (int ma = 0; ma < count; ma++)
			for (int mi = ma + 1; mi < count; mi++)
			{
				if (arrays[mi] < arrays[ma])
				{
					char mai = arrays[mi];
					arrays[mi] = arrays[ma];
					arrays[ma] = mai;
				}
			}
		for (int j = 0; j < count; j++)
		{
			if (color == arrays[j])color++;
		}
		a[k] = color;
		checknode[k] = true;
		PHI<int> kq;
		kq.one = k + 1;
		kq.two = a[k];
		/*string kq = "";
		kq=kq+(char)(k + 48 + 1) + a[k];*/
		colors.AddL(kq);
	}

	return colors;
}

bool MyGraph::Connectivity()const
{
	bool *checknode = new bool[this->_n];
	Stack<int> road;
	List<int> newroad;
	for (int i = 0; i < this->_n; i++) {
		checknode[i] = false;
	}
	bool finish = false;
	road.Push(0);
	DFSmain(checknode, road, 0, this->_n + 1, finish);
	for (int i = 0; i < this->_n; i++)
	{
		if (!checknode[i]) return false;
	}
	return true;
}
List<PHI<int>> MyGraph::Prim()const {
	List<PHI<int>> result;
	if (Connectivity())
	{
		MyGraph newgraphic(this->_n);
		newgraphic._n = this->_n;
		List<PHI<int>> box;
		int count = 0;
		int min;
		int min_count;
		int number_rad = 0;
		bool *checknode = new bool[this->_n];
		int checknode_count = 1;
		for (int i = 0; i < this->_n; i++) checknode[i] = false;
		int ki = -1;
		//newgraphic.GraphicOut();
		while (checknode_count != this->_n - 1)
		{
			if (ki != number_rad)
			{
				ki = number_rad;
				checknode[ki] = true;
				/*add to list*/
				for (int j = 0; j < this->_n; j++)
				{
					if (!checknode[j] && this->_matrix[ki][j] != 0)
					{
						PHI<int> ka;
						ka.oma = this->_matrix[ki][j];
						ka.one = ki;
						ka.two = j;
						box.AddL(ka);
					}
				}
			}
			//get min
			min = box.Value(0).oma;
			min_count = 0;
			for (int i = 1; i < box.Length(); i++)
			{
				if (min > box.Value(i).oma)
				{
					min = box.Value(i).oma;
					min_count = i;
				}
			}
			if (newgraphic.DFS(box.Value(min_count).one + 1, box.Value(min_count).two + 1).empty())
			{
				newgraphic.setEdge(box.Value(min_count).one + 1, box.Value(min_count).two + 1, 'N', box.Value(min_count).oma);
				//newgraphic.GraphicOut();
				/*string a = "";a=a+(char)(box.Value(min_count).one + 48 + 1) + " - " + (char)(box.Value(min_count).two + 48 + 1);*/
				PHI<int> a = box.Value(min_count);
				result.AddL(a);
				//cout <<checknode_count<<" " <<box.Value(min_count).one + 1 << " - " << box.Value(min_count).two + 1 << endl;
				checknode[box.Value(min_count).two] = true;
				number_rad = box.Value(min_count).two;
				checknode_count++;
			}
			box.Delete(min_count);
		}
	}
	return result;
}
List<PHI<int>> MyGraph::Kruskal()const {
	List<PHI<int>> result;
	if (Connectivity())
	{
		PHI<int> array[100];
		int count = 0;
		for (int i = 0; i < this->_n; i++)
		{
			for (int j = i; j < this->_n; j++)
			{
				if (this->_matrix[i][j] != 0)
				{
					array[count].one = i;
					array[count].two = j;
					array[count].oma = this->_matrix[i][j];
					count++;
				}
			}
		}
		for (int i = 0; i < count; i++)
			for (int j = i + 1; j < count; j++)
			{
				if (array[i].oma > array[j].oma)
				{
					PHI<int> ka = array[i];
					array[i] = array[j];
					array[j] = ka;
				}
			}
		
		MyGraph newgraphic(this->_n);
		newgraphic._n = this->_n;
		for (int i = 0; i < count; i++)
		{
			if (newgraphic.DFS(array[i].one + 1, array[i].two + 1).empty())
			{
				newgraphic.setEdge(array[i].one + 1, array[i].two + 1, 'N', array[i].oma);
				//newgraphic.GraphicOut();
				//string a = ""; a = a + (char)(array[i].one + 48 + 1) + " - " + (char)(array[i].two + 48 + 1);
				PHI<int> a = array[i];
				result.AddL(a);
				//cout <<checknode_count<<" " <<box.Value(min_count).one + 1 << " - " << box.Value(min_count).two + 1 << endl;
			}
		}
	}
	return result;
}


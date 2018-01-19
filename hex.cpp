#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <string>
#include <sstream>
#include <range/v3/all.hpp>
#include "glm/ext.hpp"
using namespace std;
using namespace glm;

class Hex : public ivec3{
public:
	Hex(): ivec3() {}
	Hex(ivec3 v): ivec3(v){}
	Hex(int i, int j) : ivec3(i,j,-i-j){}
	Hex(float i, float j, float k){
	 	int rx = round(i);
	    int ry = round(j);
	    int rz = round(k);

	    float x_diff = abs(rx - i);
	    float y_diff = abs(ry - j);
	    float z_diff = abs(rz - k);

	    if(x_diff > y_diff && x_diff > z_diff){
	        rx = -ry-rz;
	    }
	    else if( y_diff > z_diff){
	        ry = -rx-rz;
	    }
	    else{
	        rz = -rx-ry;
	    }

    	x = rx;
    	y = ry;
    	z = rz;
	}

	int distance(Hex b) const {
		return (abs(x - b.x) + abs(y - b.y) + abs(z - b.z)) / 2;
	}
	static vector<Hex> line(const Hex a,const Hex b){
		int N = a.distance(b);
		cout<<"numpts " << N+1;
		return ranges::view::linear_distribute(0.0f, 1.0f, N+1) | ranges::view::transform(
				[&](auto t){ return hex_lerp(a, b, t);}
			);
	}
	static float lerp(const float a, const float b, const float t){
		return a + (b - a) * t;
	}
	static Hex hex_lerp(const Hex a, const Hex b,const float t){
		return Hex{ lerp(a.x, b.x, t)+.000001f,
					lerp(a.y, b.y, t)+.000001f,
					lerp(a.z, b.z, t)-.000002f };
	}
};
static const vector<Hex> axial_directions{
	Hex(+1,  0), Hex(+1, -1), Hex( 0, -1),
	Hex(-1,  0), Hex(-1, +1), Hex( 0, +1)
};

std::vector<Hex> neighbors(Hex c){
	return axial_directions | ranges::view::transform( [=](auto n){return c+n;});
};


string print_map(int n, std::vector<Hex> v, vector<Hex> pts){
	int h = n*2 - 1;
	stringstream sb;
	for(int i=0; i < h; i++){
		int slope = abs((i+1) - n);
		int numcells = n+(n-1)- abs((i+1) - n);


		int ex = - std::min(i, n);
		int wy = 1-(n-i) ;
		for(int s =0; s < slope; s++){
			sb<<" ";
		}
		for(int j=0; j < numcells; j++){
			Hex pos{ex+j, wy};
			
		 	if(ranges::find(pts, pos) != pts.end()){
				sb<<"# ";
			}else if(ranges::find(v, pos) != v.end()){
				sb<<"* ";
			}
			else{
				sb<<"_ ";
			}
		}
		for(int s =0; s < slope; s++){
			sb<<" ";
		}
		sb<<wy<<endl;
	}
	return sb.str();
}

using Item = int;
class TileObject{
public:
	Hex position;
	int id;
	Item storage = 0;
	Item input = 0;
	Item output = 0;
	std::vector<TileObject*> neighbors;
	int curN;
	void update(){
		if(storage > 0){
			storage--;
			output++;
		}
		storage += input;
		input = 0;
	}

	Item insert(Item i){
		input += i;
		return 0;
	}
	void postUpdate(){
		if(neighbors.size() == 0) return;
		output = neighbors[curN]->insert(output);
		cout<<"Moving from "<< neighbors[curN]->input<<endl;
		curN = (curN + 1) % neighbors.size();
	}
}; 


int main(int argc, char** argv){

	int mapsize = atoi(argv[1]);
	int ptbx = atoi(argv[2]);
	int ptby = atoi(argv[3]);
	Hex hexa(0,0);
	Hex hexb(ptbx, ptby);

	auto lines = Hex::line(hexa, hexb);
	vector<TileObject*> inserters;
	for(int i=0; i < lines.size(); i++){
		TileObject* o=new TileObject();
		o->id = i;
		o->position = lines[i];
		if(i >=1){
			o->neighbors.push_back(inserters[i-1]);
		}
		inserters.push_back(o);
	}
	inserters.back()->storage = 10;
	for(int i=0; i < 10; i++){
		cout<<"Tick " << i <<endl;
		for(auto &c: inserters){
			c->update();
			cout<<c->id << ": " << c->storage << endl;
		}
		for(auto& c: inserters){
			c->postUpdate();
		}
}	

}

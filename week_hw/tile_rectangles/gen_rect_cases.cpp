#include "base.cpp"

Rect gen_Rect(const int w_up, const int w_low, const int h_up, const int h_low){ //maybe have
  Rect temp_rect((rand()%(w_up - w_low)) + w_low, (rand()%(h_up - h_low) + h_low));
  return temp_rect;
}

vector<Rect> gen_Rect_vects(const int w_up, const int w_low, const int h_up, const int h_low, const int vec_size){
  vector<Rect> rect_vec;
  for(int i = 0; i < vec_size; ++i){
    rect_vec.push_back(gen_Rect(w_up, w_low, h_up, h_low));
  }
  return rect_vec;
}

int main(){
  srand(1); //setting seed
  
  ifstream fin("rect_params.txt");
  ofstream fout("rect_cases.txt");

  int w_up, w_low, h_up, h_low, vec_size;

  fin >> w_up >> w_low >> h_up >> h_low >> vec_size;

  fout << vec_size << endl;

  for(const auto &elem: gen_Rect_vects(w_up, w_low, h_up, h_low, vec_size)){
    fout << elem.width << " " << elem.height << endl;
  }
  return 0;
}

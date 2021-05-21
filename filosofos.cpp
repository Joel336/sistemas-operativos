#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class Chopstics
{
  public:
  Chopstics(){;}
  mutex mu;
};

class tiempo
{
  public:
  int time;
  auto endT(float timed){
  }
};

int main()
{
  int filosof, seg, com = 20, k;
  cout << "Numero de filosofos: ";
  cin >> filosof ;

  seg = 1000;
  tiempo temp;

  temp.time = seg;

  while (k < com)
  {

    int ms = temp.time;
    auto start = chrono::high_resolution_clock::now();

    auto eat = [ms](Chopstics &left_chopstics, Chopstics &right_chopstics, int philosopher_number)
    {

      unique_lock<mutex> llock(left_chopstics.mu);
      unique_lock<mutex> rlock(right_chopstics.mu);

      cout << "Filosofo " << philosopher_number << " esta comiendo\n";

      chrono::milliseconds timeout(ms);
      this_thread::sleep_for(timeout);

      cout << "Filosofo " << philosopher_number << " termino de comer\n";
    };

    Chopstics chp[filosof];
    thread philosopher[filosof];

    cout << "Filosofo 1 esta pensando\n";
    philosopher[0] = thread(eat, ref(chp[0]), ref(chp[filosof - 1]), 1);

    for(int i = 1; i < filosof; ++i)
    {
      cout << "Filosofo " << (i+1) << " esta pensando\n";

      philosopher[i] = thread(eat, ref(chp[i]), ref(chp[i - 1]), (i + 1));
    }

    for(auto &ph: philosopher)
    {
      ph.join();
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration <float> duration = end - start;
    temp.endT(duration.count());
    k++;
    cout<<"Comida sobrante: "<< com - k << endl;
  }
}

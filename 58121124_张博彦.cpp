#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<random>
using namespace std;
#define dimension 10//问题的维度
#define Precision 1.0e-6//精度

void print_alpha(double* a)
{
	for (int i = 0; i < dimension; i++)
	{
		cout << "a[" << i << "] = " << fixed << setprecision(6) << a[i] << endl;
	}
	cout << endl;
}
//打印数组alpha
void print_x(double* x)
{
	double sum = 0.0;
	for (int i = 0; i < dimension; i++)
	{
		sum += x[i];
		cout << "   x[" << i << "] = " << fixed << setprecision(6) << x[i] << endl;
	}
	cout << endl;
	cout << "total water is " << fixed << setprecision(6) << sum << endl;//打印出在water_volume下，注入的总水量
}
//打印数组x
double caculate_target(double* alpha, double* x)
{
	double finalResult = 0.0;
	for (int i = 0; i < dimension; i++)
	{
		finalResult += log(alpha[i] + x[i]);
	}
	return -finalResult;
}
//返回所求目标值
double max(double num)
{
	if (num > 0) return num;
	else return 0.0;
}
//判断num和0的大小
double caculate_current_total_water(double* alpha, double water_volume)
{
	double current = 0.0;

	for (int i = 0; i < dimension; i++)
	{
		current += max(water_volume - alpha[i]);
	}

	return current;
}
//计算在water_volume下，所需要注入的总水量
double fill_water(double* alpha, double total_water, double precision)
{
	double x[dimension] = { 0 };
	double water_volume = 1.0;//此处为方便，将初始水容量(1/v)设置为1.0
	int count = 0;//记录逼近目标水容量的次数
	double curr_water = caculate_current_total_water(alpha, water_volume);//记录在water_volume时，应该注入的总水量

	while (count < 20 && curr_water != total_water)//当已经执行完了设置的逼近次数或加入的水量恰好等于总水量时，循环才会结束
	{
		//将当前的总注水量减去目标总水量，得到两者差值，再平均到每一片区域上，即为water_volume下一次需要减少的值，随之不断的执行，在无需注水的地方增加（减少）的差值会逐步减小直至趋于0
		// 即在当前1.0e-6的精度下，该差值不会影响最后的总注水量
		//当然此处的逼近方法可能比较粗糙,计算的逼近次数也可能不是最优逼近次数
		//并且根据多次的运行结果，在逼近15-20的次数下，该方法能够稳定求出标准的结果
		water_volume -= (curr_water - total_water) / dimension;

		curr_water = caculate_current_total_water(alpha, water_volume);
		count++;
	}

	for (int i = 0; i < dimension; i++)
	{
		x[i] = max(water_volume - alpha[i]);
	}

	print_x(x);
	cout << "water_volume = " << water_volume << endl;
	cout << endl;
	return caculate_target(alpha,x);
}
//根据数组alpha计算注水量
void random(double* a)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < dimension; i++)
	{
		a[i] = rand() % 1000000 * 1.0 / 100000;//此处由于随机数的最大值无法达到6位，因此本应/1000000，此处却使用/100000替代，使得第一位小数能够取到除0以外的数
	}
}
//对数组a生成随机数
int main()
{
	double alpha[dimension] = { 0 };
	double total_water = 1.0;

	random(alpha);
	print_alpha(alpha);
	double minimize = fill_water(alpha, total_water, Precision);
	cout << "   minimize = " << fixed << setprecision(6) << minimize << endl;
}
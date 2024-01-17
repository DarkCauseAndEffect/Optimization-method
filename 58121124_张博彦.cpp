#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<random>
using namespace std;
#define dimension 10//�����ά��
#define Precision 1.0e-6//����

void print_alpha(double* a)
{
	for (int i = 0; i < dimension; i++)
	{
		cout << "a[" << i << "] = " << fixed << setprecision(6) << a[i] << endl;
	}
	cout << endl;
}
//��ӡ����alpha
void print_x(double* x)
{
	double sum = 0.0;
	for (int i = 0; i < dimension; i++)
	{
		sum += x[i];
		cout << "   x[" << i << "] = " << fixed << setprecision(6) << x[i] << endl;
	}
	cout << endl;
	cout << "total water is " << fixed << setprecision(6) << sum << endl;//��ӡ����water_volume�£�ע�����ˮ��
}
//��ӡ����x
double caculate_target(double* alpha, double* x)
{
	double finalResult = 0.0;
	for (int i = 0; i < dimension; i++)
	{
		finalResult += log(alpha[i] + x[i]);
	}
	return -finalResult;
}
//��������Ŀ��ֵ
double max(double num)
{
	if (num > 0) return num;
	else return 0.0;
}
//�ж�num��0�Ĵ�С
double caculate_current_total_water(double* alpha, double water_volume)
{
	double current = 0.0;

	for (int i = 0; i < dimension; i++)
	{
		current += max(water_volume - alpha[i]);
	}

	return current;
}
//������water_volume�£�����Ҫע�����ˮ��
double fill_water(double* alpha, double total_water, double precision)
{
	double x[dimension] = { 0 };
	double water_volume = 1.0;//�˴�Ϊ���㣬����ʼˮ����(1/v)����Ϊ1.0
	int count = 0;//��¼�ƽ�Ŀ��ˮ�����Ĵ���
	double curr_water = caculate_current_total_water(alpha, water_volume);//��¼��water_volumeʱ��Ӧ��ע�����ˮ��

	while (count < 20 && curr_water != total_water)//���Ѿ�ִ���������õıƽ�����������ˮ��ǡ�õ�����ˮ��ʱ��ѭ���Ż����
	{
		//����ǰ����עˮ����ȥĿ����ˮ�����õ����߲�ֵ����ƽ����ÿһƬ�����ϣ���Ϊwater_volume��һ����Ҫ���ٵ�ֵ����֮���ϵ�ִ�У�������עˮ�ĵط����ӣ����٣��Ĳ�ֵ���𲽼�Сֱ������0
		// ���ڵ�ǰ1.0e-6�ľ����£��ò�ֵ����Ӱ��������עˮ��
		//��Ȼ�˴��ıƽ��������ܱȽϴֲ�,����ıƽ�����Ҳ���ܲ������űƽ�����
		//���Ҹ��ݶ�ε����н�����ڱƽ�15-20�Ĵ����£��÷����ܹ��ȶ������׼�Ľ��
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
//��������alpha����עˮ��
void random(double* a)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < dimension; i++)
	{
		a[i] = rand() % 1000000 * 1.0 / 100000;//�˴���������������ֵ�޷��ﵽ6λ����˱�Ӧ/1000000���˴�ȴʹ��/100000�����ʹ�õ�һλС���ܹ�ȡ����0�������
	}
}
//������a���������
int main()
{
	double alpha[dimension] = { 0 };
	double total_water = 1.0;

	random(alpha);
	print_alpha(alpha);
	double minimize = fill_water(alpha, total_water, Precision);
	cout << "   minimize = " << fixed << setprecision(6) << minimize << endl;
}
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace std;

[STAThreadAttribute]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Project1::MyForm form;
	Application::Run(% form);

}

System::Void Project1::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e)//Данные
{
	if (textBox1->Text == "" || textBox2->Text == "")
	{
		DefaultParams();
		textBox1->Text = Convert::ToString(size);
		textBox2->Text = Convert::ToString(tact);
	}
	else
	{
		size = Convert::ToInt16(textBox1->Text);
		tact = Convert::ToInt16(textBox2->Text);
	}

	process* arr = new process[size];
	for (int i = 0; i < size; i++)
	{
		createMas(arr[i]);
	}
	int sizeLow = 0, sizeHigh = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i].priority == 1)
		{
			sizeHigh++;
		}
		else
		{
			sizeLow++;
		}
	}

	process* arrHigh = new process[sizeHigh];
	process* arrLow = new process[sizeLow];

	for (int i = 0, j = 0, k = 0; i < size; i++)
	{
		if (arr[i].priority == 1)
		{
			arrHigh[j] = arr[i];
			j++;
		}
		else
		{
			arrLow[k] = arr[i];
			k++;
		}
	}


	if (sizeHigh == 0)
	{
		MessageBox::Show("Очередь Round-robin пуста");
	}
	else
	{
		int nowWork = 0;
		int done = 0;
		string* str = new string[sizeHigh];

		int t = 0;

		while (done < sizeHigh)
		{
			if (t % tact == 0 && t != 0)
			{
				nowWork++;
				if (nowWork >= sizeHigh)
				{
					nowWork = 0;
				}
				t = 0;
			}
			if (arrHigh[nowWork].mas[arrHigh[nowWork].index] != 'И')
			{
				nowWork++;
				if (nowWork >= sizeHigh)
				{
					nowWork = 0;
				}
				t = 0;
			}


			if (arrHigh[nowWork].mas[arrHigh[nowWork].index] == 'И')
			{
				t++;
				str[nowWork] += ' ';
				str[nowWork] += arrHigh[nowWork].mas[arrHigh[nowWork].index];
				arrHigh[nowWork].index++;

				for (int i = 0; i < sizeHigh; i++)
				{
					if (i != nowWork)
					{
						if (arrHigh[i].mas[arrHigh[i].index] == '\0')
						{
							continue;
						}
						else if (arrHigh[i].mas[arrHigh[i].index] == 'И')
						{
							str[i] += ' ';
							str[i] += 'Г';
						}
						else if (arrHigh[i].mas[arrHigh[i].index] == 'О')
						{
							str[i] += ' ';
							str[i] += 'О';
							arrHigh[i].index++;
						}
					}
				}
			}

			if (sizeHigh - done == 1)
			{
				while (arrHigh[nowWork].mas[arrHigh[nowWork].index] != '\0')
				{
					str[nowWork] += ' ';
					str[nowWork] += arrHigh[nowWork].mas[arrHigh[nowWork].index];
					arrHigh[nowWork].index++;
				}
			}

			if (arrHigh[nowWork].mas[arrHigh[nowWork].index] == '\0')
			{
				if (arrHigh[nowWork].done == 0)
				{
					arrHigh[nowWork].done++;
					str[nowWork] += ' ';
					str[nowWork] += 'З';
					done++;
					continue;
				}
			}

		}

		dataGridView1->RowCount = sizeHigh;
		dataGridView1->ColumnCount = 1;

		dataGridView1->TopLeftHeaderCell->Value = "Процесс Round-robin";
		dataGridView1->AutoResizeColumns();

		for (int i = 0; i < dataGridView1->RowCount; i++)
		{
			string mes = str[i];
			String^ mess = gcnew System::String(mes.c_str());

			dataGridView1->Rows[i]->HeaderCell->Value = Convert::ToString(i + 1);
			dataGridView1->Rows[i]->Cells[0]->Value = mess;
		}

		dataGridView1->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders);
		dataGridView1->AutoResizeColumns();
	}

	if (sizeLow == 0)
	{
		MessageBox::Show("Очередь FCFS пуста");
	}
	else
	{
		int nowWork = 0;
		int done = 0;
		string* str = new string[sizeLow];

		while (done != sizeLow)
		{
			if (arrLow[nowWork].mas[arrLow[nowWork].index] == '\0')
			{
				if (arrLow[nowWork].done == 0)
				{
					arrLow[nowWork].done++;
					str[nowWork] += ' ';
					str[nowWork] += 'З';
					arrLow[nowWork].willingness = 0;
					done++;
					continue;
				}
			}


			if (arrLow[nowWork].mas[arrLow[nowWork].index] != '\0')
			{
				while (arrLow[nowWork].mas[arrLow[nowWork].index] != 'О')
				{
					str[nowWork] += ' ';
					str[nowWork] += arrLow[nowWork].mas[arrLow[nowWork].index];
					arrLow[nowWork].index++;

					for (int i = 0; i < sizeLow; i++)
					{
						if (i != nowWork)
						{
							if (arrLow[i].mas[arrLow[i].index] == '\0')
							{
								arrLow[i].willingness = 0;
								continue;
							}
							else if (arrLow[i].mas[arrLow[i].index] == 'И')
							{
								str[i] += ' ';
								str[i] += 'Г';
								arrLow[i].willingness++;
							}
							else if (arrLow[i].mas[arrLow[i].index] == 'О')
							{
								str[i] += ' ';
								str[i] += 'О';
								arrLow[i].index++;
								arrLow[i].willingness = 0;
							}
						}
					}
					if (arrLow[nowWork].mas[arrLow[nowWork].index] == '\0')
					{
						if (arrLow[nowWork].done == 0)
						{
							arrLow[nowWork].willingness = 0;
							arrLow[nowWork].done++;
							str[nowWork] += ' ';
							str[nowWork] += 'З';
							done++;
							break;
						}
					}
				}
			}
			arrLow[nowWork].willingness = 0;
			nowWork = findMax(sizeLow, arrLow, nowWork);
		}

		dataGridView2->RowCount = sizeLow;
		dataGridView2->ColumnCount = 1;

		dataGridView2->TopLeftHeaderCell->Value = "Процесс FCFS";
		dataGridView2->AutoResizeColumns();

		for (int i = 0; i < dataGridView2->RowCount; i++)
		{
			string mes = str[i];
			String^ mess = gcnew System::String(mes.c_str());

			dataGridView2->Rows[i]->HeaderCell->Value = Convert::ToString(i + 1);
			dataGridView2->Rows[i]->Cells[0]->Value = mess;
		}

		dataGridView2->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders);
		dataGridView2->AutoResizeColumns();
	}

	string tmp = "";
	for (int i = 0; i < size; i++)
	{
		tmp += print(arr[i], size, i + 1);
	}

	String^ message = gcnew System::String(tmp.c_str());
	MessageBox::Show(message);
}

void Project1::MyForm::DefaultParams()
{
	size = 10;
	tact = 2;
}

int Project1::MyForm::getPriority()
{
	random_device random_device;
	mt19937 generator(random_device());
	uniform_int_distribution<> distribution(0, 1);

	return distribution(generator);
}

void Project1::MyForm::createMas(process& prcss)
{
	random_device random_device;
	mt19937 generator(random_device());
	uniform_int_distribution<> distribution(1, 10);
	int size = distribution(generator);
	char* mas = new char[size];

	uniform_int_distribution<> boolDistribution(0, 1);

	for (int i = 0; i < 1; i++)
	{
		*(mas + i) = 'И';

	}

	for (int i = 1; i < size - 1; i++)
	{
		int rnd = boolDistribution(generator);
		if (rnd == 0)
		{
			*(mas + i) = 'И';
		}
		else
		{
			*(mas + i) = 'О';
		}
	}

	for (int i = size - 1; i < size; i++)
	{
		*(mas + i) = 'И';
	}

	mas[size] = '\0';

	prcss.mas = mas;
	prcss.priority = getPriority();
}

string Project1::MyForm::print(process arr, int size,int index)
{
	for (int i = 0, j; i < size; i++)
	{
		j = 0;

		string message=to_string(index);
		message += ": ";

		while (arr.mas[j] != '\0')
		{
			message += arr.mas[j];
			message += " ";
			j++;
		}

		message += "\t\t\t";

		if (arr.priority == 1)
		{
			message+= "| Высокий приоритет";
			
		}
		else
		{
			message += "| Низкий приоритет";
		}
		message += "\n";
		return message;
	}
}

int Project1::MyForm::findMax(int size, process arr[], int nowWork)
{
	int* maxValue = new int[size];

	for (int i = 0; i < size; i++)
	{
		maxValue[i] = 0;
		if (i != nowWork && arr[i].done == 0)
		{
			maxValue[i] = arr[i].willingness;
		}
	}
	int max = 0;
	int maxIndex = nowWork;
	for (int i = 0; i < size; i++)
	{
		if (maxValue[i] > max)
		{
			max = maxValue[i];
			maxIndex = i;
		}
	}

	return maxIndex;
}
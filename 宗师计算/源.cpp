#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
// �۸�ṹ�嶨��
struct Price {
	int gold;   // ��
	int silver; // ��
	int copper; // ͭ

	int toCopper() const;
	static Price fromCopper(int totalCopper);
};

// ��ʽ������۸�
ostream& operator<<(ostream& os, const Price& p);

// �����Ʒ��������
void addProduct(unordered_map<string, Price>& products, const string& fileName);
void viewProducts(const unordered_map<string, Price>& products);
void updateProduct(unordered_map<string, Price>& products, const string& fileName);
void deleteProduct(unordered_map<string, Price>& products, const string& fileName);
void saveProducts(const unordered_map<string, Price>& products, const string& fileName);
void loadProducts(unordered_map<string, Price>& products, const string& fileName);

// �۸�ṹ���Ա��������
int Price::toCopper() const {
	return gold * 10000 + silver * 100 + copper;
}

Price Price::fromCopper(int totalCopper) {
	Price p;
	p.gold = totalCopper / 10000;
	p.silver = (totalCopper % 10000) / 100;
	p.copper = totalCopper % 100;
	return p;
}

// ��ʽ������۸�
ostream& operator<<(ostream& os, const Price& p) {
	os << p.gold << "�� " << p.silver << "�� " << p.copper << "ͭ";
	return os;
}

// �����Ʒ
void addProduct(unordered_map<string, Price>& products, const string& fileName) {
	string name;
	Price price;
	cout << "��������Ʒ���ƣ�";
	cin.ignore();  // ���Ի��з�
	getline(cin, name);
	cout << "������ " << name << " �ļ۸񣨽� �� ͭ����";
	cin >> price.gold >> price.silver >> price.copper;
	products[name] = price;
	cout << "��Ʒ��ӳɹ���\n";
	saveProducts(products, fileName);  // ���浽�ļ�
}

// �鿴��Ʒ
void viewProducts(const unordered_map<string, Price>& products) {
	if (products.empty()) {
		cout << "û����Ʒ��¼��\n";
		return;
	}
	cout << "��Ʒ�б�\n";
	for (const auto& item : products) {
		cout << item.first << " : " << item.second << endl;
	}
}

// ������Ʒ
void updateProduct(unordered_map<string, Price>& products, const string& fileName) {
	string name;
	cout << "������Ҫ���µ���Ʒ���ƣ�";
	cin.ignore();  // ���Ի��з�
	getline(cin, name);

	auto it = products.find(name);
	if (it == products.end()) {
		cout << "��Ʒδ�ҵ���\n";
		return;
	}

	Price newPrice;
	cout << "�������¼۸񣨽� �� ͭ����";
	cin >> newPrice.gold >> newPrice.silver >> newPrice.copper;
	it->second = newPrice;
	cout << "��Ʒ�۸���³ɹ���\n";
	saveProducts(products, fileName);  // ���浽�ļ�
}

// ɾ����Ʒ
void deleteProduct(unordered_map<string, Price>& products, const string& fileName) {
	string name;
	cout << "������Ҫɾ������Ʒ���ƣ�";
	cin.ignore();  // ���Ի��з�
	getline(cin, name);

	auto it = products.find(name);
	if (it == products.end()) {
		cout << "��Ʒδ�ҵ���\n";
		return;
	}

	products.erase(it);
	cout << "��Ʒ��ɾ����\n";
	saveProducts(products, fileName);  // ���浽�ļ�
}

// ������Ʒ��Ϣ���ļ�
void saveProducts(const unordered_map<string, Price>& products, const string& fileName) {
	ofstream outFile(fileName);
	if (outFile.is_open()) {
		for (const auto& item : products) {
			outFile << item.first << " " << item.second.toCopper() << endl;
		}
		outFile.close();
		cout << "��Ʒ��Ϣ�ѱ��档\n";
	}
	else {
		cerr << "�޷����ļ�����д�롣\n";
	}
}

// ���ļ�������Ʒ��Ϣ
void loadProducts(unordered_map<string, Price>& products, const string& fileName) {
	ifstream inFile(fileName);
	if (inFile.is_open()) {
		string name;
		int totalCopper;
		while (inFile >> name >> totalCopper) {
			products[name] = Price::fromCopper(totalCopper);
		}
		inFile.close();
		cout << "��Ʒ��Ϣ�Ѽ��ء�\n";
	}
	else {
		cerr << "û���ҵ��۸��ļ����������µ��ļ���" << endl;
	}
}
// ����۸���ӵ���Ʒ�б�
void calculateAndAddProduct(unordered_map<string, Price>& products, const string& fileName)
{
	/** ��ѿƤ���� **/
	// ȷ����Ʒ�۸��Ѿ�����
	if (products.find("����") == products.end() || products.find("����") == products.end() || products.find("��ɫԴ������") == products.end()) {
		cerr << "��Ҫ����Ӵ��ס����׺ͺ�ɫԴ�������ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ���� = products["����"];
	Price ���� = products["����"];
	Price ��ɫԴ������ = products["��ɫԴ������"];

	// ������ѿƤ���͵ļ۸�
	int ��ɫԴ���������� = 3;
	int �������� = 20;
	int �������� = 20;

	int �ܹ�ͭ�ļ۸� = ��ɫԴ���������� * ��ɫԴ������.toCopper() +
		�������� * ����.toCopper() +
		�������� * ����.toCopper();

	Price �²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// �����ѿƤ���͵���Ʒ�б�
	products["��ѿƤ����"] = �²�Ʒ�۸�;
	cout << "��ѿƤ���͵ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/** Ƥ�� **/
	if (products.find("��Ƥ") == products.end()) {
		cerr << "��Ҫ�����Ƥ��ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ��Ƥ = products["��Ƥ"];


	// ���� Ƥ�� �ļ۸�
	int ��Ƥ���� = 3;


	�ܹ�ͭ�ļ۸� = ��Ƥ���� * ��Ƥ.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� Ƥ�� ����Ʒ�б�
	products["Ƥ��"] = �²�Ʒ�۸�;
	cout << "Ƥ��ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** ����Ƥ�� **/
	if (products.find("Ƥ��") == products.end() || products.find("��ѿƤ����") == products.end()) {
		cerr << "��Ҫ�����Ƥ�����ѿƤ���͵ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price Ƥ�� = products["Ƥ��"];
	Price ��ѿƤ���� = products["��ѿƤ����"];


	// ��������Ƥ��ļ۸�
	int Ƥ������ = 10;
	int ��ѿƤ�������� = 1;


	�ܹ�ͭ�ļ۸� = Ƥ������ * Ƥ��.toCopper() +
		��ѿƤ�������� * ��ѿƤ����.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// �������Ƥ�ﵽ��Ʒ�б�
	products["����Ƥ��"] = �²�Ʒ�۸�;
	cout << "����Ƥ��ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/* ����Ƥ���� */
	if (products.find("��ɫԴ������") == products.end() || products.find("����") == products.end() || products.find("С��") == products.end() || products.find("��ɫɺ����") == products.end()) {
		cerr << "��Ҫ����Ӻ�ɫԴ������ ���� С�� ��ɫɺ���ݵļ۸�\n";
		return;
	}
	// ��ȡ��֪��Ʒ�ļ۸�
	��ɫԴ������ = products["��ɫԴ������"];
	Price ���� = products["����"];
	Price С�� = products["С��"];
	Price ��ɫɺ���� = products["��ɫɺ����"];

	// ��������Ƥ���͵ļ۸�
	��ɫԴ���������� = 5;
	int �������� = 30;
	int С������ = 30;
	int ��ɫɺ�������� = 20;

	�ܹ�ͭ�ļ۸� = ��ɫԴ���������� * ��ɫԴ������.toCopper() +
		�������� * ����.toCopper() +
		С������ * С��.toCopper() +
		��ɫɺ�������� * ��ɫɺ����.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ����Ƥ�� ����Ʒ�б�
	products["����Ƥ����"] = �²�Ʒ�۸�;
	cout << "����Ƥ���� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/* ��ƤƤ�� */
	if (products.find("ͥԺ�����ط�ĩ") == products.end() || products.find("����Ƥ����") == products.end() || products.find("����Ƥ��") == products.end()) {
		cerr << "��Ҫ����� ͥԺ�����ط�ĩ ����Ƥ���� ����Ƥ�� �ļ۸�\n";
		return;
	}
	// ��ȡ��֪��Ʒ�ļ۸�
	Price ͥԺ�����ط�ĩ = products["ͥԺ�����ط�ĩ"];
	Price ����Ƥ���� = products["����Ƥ����"];
	Price ����Ƥ�� = products["����Ƥ��"];

	// ���� ��ƤƤ�� �ļ۸�
	int ͥԺ�����ط�ĩ���� = 5;
	int ����Ƥ�������� = 1;
	int ����Ƥ������ = 10;


	�ܹ�ͭ�ļ۸� = ͥԺ�����ط�ĩ���� * ͥԺ�����ط�ĩ.toCopper() +
		����Ƥ�������� * ����Ƥ����.toCopper() +
		����Ƥ������ * ����Ƥ��.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ��ƤƤ�� ����Ʒ�б�
	products["��ƤƤ��"] = �²�Ʒ�۸�;
	cout << "��ƤƤ�� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** ���ɶ� **/
	if (products.find("���ƿ�ʯ") == products.end()) {
		cerr << "��Ҫ����� ���ƿ�ʯ �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ���ƿ�ʯ = products["���ƿ�ʯ"];


	// ���� ���ɶ� �ļ۸�
	int ���ƿ�ʯ���� = 3;


	�ܹ�ͭ�ļ۸� = ���ƿ�ʯ���� * ���ƿ�ʯ.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ���ɶ� ����Ʒ�б�
	products["���ɶ�"] = �²�Ʒ�۸�;
	cout << "���ɶ� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/* ���͵���ƤƤ�� */
	if (products.find("��ƤƤ��") == products.end() || products.find("���ɶ�") == products.end() || products.find("�ȶ������Ǿ���") == products.end() || products.find("�һ�ԭľ") == products.end()) {
		cerr << "��Ҫ����� ��ƤƤ�� ���ɶ� �ȶ������Ǿ��� �һ�ԭľ �ļ۸�\n";
		return;
	}
	// ��ȡ��֪��Ʒ�ļ۸�
	Price ��ƤƤ�� = products["��ƤƤ��"];
	Price ���ɶ� = products["���ɶ�"];
	Price �ȶ������Ǿ��� = products["�ȶ������Ǿ���"];
	Price �һ�ԭľ = products["�һ�ԭľ"];
	// ���� ��ƤƤ�� �ļ۸�
	int ��ƤƤ������ = 10;
	int ���ɶ����� = 9;
	int �ȶ������Ǿ������� = 25;
	int �һ�ԭľ���� = 6;

	�ܹ�ͭ�ļ۸� = ��ƤƤ������ * ��ƤƤ��.toCopper() +
		���ɶ����� * ���ɶ�.toCopper() +
		�ȶ������Ǿ������� * �ȶ������Ǿ���.toCopper() +
		�һ�ԭľ���� * �һ�ԭľ.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ���͵���ƤƤ�� ����Ʒ�б�
	products["���͵���ƤƤ��"] = �²�Ʒ�۸�;
	cout << "���͵���ƤƤ�� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/* ���Ƥ���� */
	if (products.find("����") == products.end() ||
		products.find("���Բ�") == products.end() ||
		products.find("�ȶ������Ǿ���") == products.end() ||
		products.find("�˻��ᾧ") == products.end() ||
		products.find("Ҭ��") == products.end()
		) {
		cerr << "��Ҫ����� ���� ���Բ� �ȶ������Ǿ��� �˻��ᾧ Ҭ�� �ļ۸�\n";
		return;
	}
	// ��ȡ��֪��Ʒ�ļ۸�
	Price ���� = products["����"];
	Price ���Բ� = products["���Բ�"];
	�ȶ������Ǿ��� = products["�ȶ������Ǿ���"];
	Price �˻��ᾧ = products["�˻��ᾧ"];
	Price Ҭ�� = products["Ҭ��"];
	// ���� ���Ƥ���� �ļ۸�
	int �������� = 50;
	int ���Բ����� = 50;
	�ȶ������Ǿ������� = 3;
	int �˻��ᾧ���� = 10;
	int Ҭ������ = 10;

	�ܹ�ͭ�ļ۸� = �������� * ����.toCopper() +
		���Բ����� * ���Բ�.toCopper() +
		�ȶ������Ǿ������� * �ȶ������Ǿ���.toCopper() +
		�˻��ᾧ���� * �˻��ᾧ.toCopper() +
		Ҭ������ * Ҭ��.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ���Ƥ���� ����Ʒ�б�
	products["���Ƥ����"] = �²�Ʒ�۸�;
	cout << "���Ƥ���� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/* �����ϵ��¹�ӻ� */
	if (products.find("ǿ���Զ���") == products.end() ||
		products.find("���Ƶļ���") == products.end() ||
		products.find("�ȶ������Ǿ���") == products.end()
		) {
		cerr << "��Ҫ����� ǿ���Զ��� ���Ƶļ��� �ȶ������Ǿ��������ļ۸�\n";
		return;
	}
	// ��ȡ��֪��Ʒ�ļ۸�
	Price ǿ���Զ��� = products["ǿ���Զ���"];
	Price ���Ƶļ��� = products["���Ƶļ���"];
	�ȶ������Ǿ��� = products["�ȶ������Ǿ���"];
	// ���� �����ϵ��¹�ӻ� �ļ۸�
	int ǿ���Զ������� = 4;
	int ���Ƶļ������� = 4;
	�ȶ������Ǿ������� = 50;

	�ܹ�ͭ�ļ۸� = ǿ���Զ������� * ǿ���Զ���.toCopper() +
		���Ƶļ������� * ���Ƶļ���.toCopper() +
		�ȶ������Ǿ������� * �ȶ������Ǿ���.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� �����ϵ��¹�ӻ� ����Ʒ�б�
	products["�����ϵ��¹�ӻ�"] = �²�Ʒ�۸�;
	cout << "�����ϵ��¹�ӻ� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;
	// ��� �����ϵ�����ӻ� ����Ʒ�б�
	products["�����ϵ�����ӻ�"] = �²�Ʒ�۸�;
	cout << "�����ϵ�����ӻ� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;
	// ��� �����ϵ��ǹ�ӻ� ����Ʒ�б�
	products["�����ϵ��ǹ�ӻ�"] = �²�Ʒ�۸�;
	cout << "�����ϵ��ǹ�ӻ� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/** ����Դ������ **/
	if (products.find("����Դ����Ƭ") == products.end()) {
		cerr << "��Ҫ����� ����Դ����Ƭ �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ����Դ����Ƭ = products["����Դ����Ƭ"];


	// ���� ����Դ������ �ļ۸�
	int ����Դ����Ƭ���� = 5;


	�ܹ�ͭ�ļ۸� = ����Դ����Ƭ���� * ����Դ����Ƭ.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ����Դ������ ����Ʒ�б�
	products["����Դ������"] = �²�Ʒ�۸�;
	cout << "����Դ������ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** ����ǿ������ **/
	if (products.find("����ǿ����ʯ") == products.end() ||
		products.find("�վ���") == products.end()) {
		cerr << "��Ҫ����� ����ǿ����ʯ �վ��� �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ����ǿ����ʯ = products["����ǿ����ʯ"];
	Price �վ��� = products["�վ���"];

	// ���� ����ǿ������ �ļ۸�
	int ����ǿ����ʯ���� = 1;
	int �վ������� = 1;


	�ܹ�ͭ�ļ۸� = ����ǿ����ʯ���� * ����ǿ����ʯ.toCopper() +
		�վ������� * �վ���.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ����ǿ������ ����Ʒ�б�
	products["����ǿ������"] = �²�Ʒ�۸�;
	cout << "����ǿ������ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/************************** Ƥ����ʦһ�װװ� **************************/
	/* ��ʦ_Ƥ��ͷ */
	if (products.find("����ǿ������") == products.end() ||
		products.find("����Դ������") == products.end() ||
		products.find("�����ϵ��¹�ӻ�") == products.end() ||
		products.find("���͵���ƤƤ��") == products.end() ||
		products.find("���Ƥ����") == products.end())
	{
		cerr << "��Ҫ����� ����ǿ������ ����Դ������ �����ϵ��¹�ӻ� ���͵���ƤƤ�� ���Ƥ���� �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ����ǿ������ = products["����ǿ����ʯ"];
	Price ����Դ������ = products["����Դ������"];
	Price �����ϵ��¹�ӻ� = products["�����ϵ��¹�ӻ�"];
	Price ���͵���ƤƤ�� = products["���͵���ƤƤ��"];
	Price ���Ƥ���� = products["���Ƥ����"];

	// ���� ��ʦ_Ƥ��ͷ �ļ۸�
	int ����ǿ���������� = 10;
	int ����Դ���������� = 82;
	int �����ϵ��¹�ӻ����� = 1;
	int ���͵���ƤƤ������ = 11;
	int ���Ƥ�������� = 35;

	�ܹ�ͭ�ļ۸� = ����ǿ���������� * ����ǿ������.toCopper() +
		����Դ���������� * ����Դ������.toCopper() +
		�����ϵ��¹�ӻ����� * �����ϵ��¹�ӻ�.toCopper() +
		���͵���ƤƤ������ * ���͵���ƤƤ��.toCopper() +
		���Ƥ�������� * ���Ƥ����.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ��ʦ_Ƥ��ͷ ����Ʒ�б�
	products["��ʦ_Ƥ��ͷ"] = �²�Ʒ�۸�;
	cout << "��ʦ_Ƥ��ͷ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/*  ���� ��ʦ_Ƥ���� �ļ۸� */
	����ǿ���������� = 10;
	����Դ���������� = 130;
	�����ϵ��¹�ӻ����� = 1;
	���͵���ƤƤ������ = 13;
	���Ƥ�������� = 35;

	�ܹ�ͭ�ļ۸� = ����ǿ���������� * ����ǿ������.toCopper() +
		����Դ���������� * ����Դ������.toCopper() +
		�����ϵ��¹�ӻ����� * �����ϵ��¹�ӻ�.toCopper() +
		���͵���ƤƤ������ * ���͵���ƤƤ��.toCopper() +
		���Ƥ�������� * ���Ƥ����.toCopper();

	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ��ʦ_Ƥ�� ����Ʒ�б�
	products["��ʦ_Ƥ����"] = �²�Ʒ�۸�;
	cout << "��ʦ_Ƥ���� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/* ���� ��ʦ_Ƥ������ �ļ۸� */
	����ǿ���������� = 10;
	����Դ���������� = 66;
	�����ϵ��¹�ӻ����� = 1;
	���͵���ƤƤ������ = 9;
	���Ƥ�������� = 35;

	�ܹ�ͭ�ļ۸� = ����ǿ���������� * ����ǿ������.toCopper() +
		����Դ���������� * ����Դ������.toCopper() +
		�����ϵ��¹�ӻ����� * �����ϵ��¹�ӻ�.toCopper() +
		���͵���ƤƤ������ * ���͵���ƤƤ��.toCopper() +
		���Ƥ�������� * ���Ƥ����.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ��ʦ_Ƥ������ ����Ʒ�б�
	products["��ʦ_Ƥ������"] = �²�Ʒ�۸�;
	cout << "��ʦ_Ƥ������ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;



	/* ���� ��ʦ_Ƥ������ �ļ۸� */
	����ǿ���������� = 10;
	����Դ���������� = 66;
	�����ϵ��¹�ӻ����� = 1;
	���͵���ƤƤ������ = 9;
	���Ƥ�������� = 35;

	�ܹ�ͭ�ļ۸� = ����ǿ���������� * ����ǿ������.toCopper() +
		����Դ���������� * ����Դ������.toCopper() +
		�����ϵ��¹�ӻ����� * �����ϵ��¹�ӻ�.toCopper() +
		���͵���ƤƤ������ * ���͵���ƤƤ��.toCopper() +
		���Ƥ�������� * ���Ƥ����.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ��ʦ_Ƥ������ ����Ʒ�б�
	products["��ʦ_Ƥ������"] = �²�Ʒ�۸�;
	cout << "��ʦ_Ƥ������ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/* ���� ��ʦ_Ƥ������ �ļ۸� */
	����ǿ���������� = 10;
	����Դ���������� = 82;
	�����ϵ��¹�ӻ����� = 1;
	���͵���ƤƤ������ = 11;
	���Ƥ�������� = 35;

	�ܹ�ͭ�ļ۸� = ����ǿ���������� * ����ǿ������.toCopper() +
		����Դ���������� * ����Դ������.toCopper() +
		�����ϵ��¹�ӻ����� * �����ϵ��¹�ӻ�.toCopper() +
		���͵���ƤƤ������ * ���͵���ƤƤ��.toCopper() +
		���Ƥ�������� * ���Ƥ����.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ��ʦ_Ƥ���ȼ� ����Ʒ�б�
	products["��ʦ_Ƥ������"] = �²�Ʒ�۸�;
	cout << "��ʦ_Ƥ������ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/* ���� ��ʦ_Ƥ���ȼ� �ļ۸� */
	����ǿ���������� = 10;
	����Դ���������� = 97;
	�����ϵ��¹�ӻ����� = 1;
	���͵���ƤƤ������ = 12;
	���Ƥ�������� = 35;

	�ܹ�ͭ�ļ۸� = ����ǿ���������� * ����ǿ������.toCopper() +
		����Դ���������� * ����Դ������.toCopper() +
		�����ϵ��¹�ӻ����� * �����ϵ��¹�ӻ�.toCopper() +
		���͵���ƤƤ������ * ���͵���ƤƤ��.toCopper() +
		���Ƥ�������� * ���Ƥ����.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ��ʦ_Ƥ���ȼ� ����Ʒ�б�
	products["��ʦ_Ƥ���ȼ�"] = �²�Ʒ�۸�;
	cout << "��ʦ_Ƥ���ȼ� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/* ���� ��ʦ_Ƥ��Ь�� �ļ۸� */
	����ǿ���������� = 10;
	����Դ���������� = 82;
	�����ϵ��¹�ӻ����� = 1;
	���͵���ƤƤ������ = 11;
	���Ƥ�������� = 35;

	�ܹ�ͭ�ļ۸� = ����ǿ���������� * ����ǿ������.toCopper() +
		����Դ���������� * ����Դ������.toCopper() +
		�����ϵ��¹�ӻ����� * �����ϵ��¹�ӻ�.toCopper() +
		���͵���ƤƤ������ * ���͵���ƤƤ��.toCopper() +
		���Ƥ�������� * ���Ƥ����.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ��ʦ_Ƥ��Ь�� ����Ʒ�б�
	products["��ʦ_Ƥ��Ь��"] = �²�Ʒ�۸�;
	cout << "��ʦ_Ƥ��Ь�� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;



	/** ����֮�� **/
	if (products.find("����֮��") == products.end()) {
		cerr << "��Ҫ����� ����֮�� �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ����֮�� = products["����֮��"];


	// ���� ����֮�� �ļ۸�
	int ����֮������ = 45;


	�ܹ�ͭ�ļ۸� = ����֮������ * ����֮��.toCopper();

	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ����֮�� ����Ʒ�б�
	products["����֮��"] = �²�Ʒ�۸�;
	cout << "����֮�� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** �ʺ緭�¼� **/
	if (products.find("�ȶ������Ǿ���") == products.end() ||
		products.find("����") == products.end() ||
		products.find("������") == products.end() ||
		products.find("�˻��ᾧ") == products.end() ||
		products.find("ɽë鷹�ʵ") == products.end()) {
		cerr << "��Ҫ����� �ȶ������Ǿ��� ���� ������ �˻��ᾧ ɽë鷹�ʵ �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	�ȶ������Ǿ��� = products["�ȶ������Ǿ���"];
	Price ���� = products["����"];
	Price ������ = products["������"];
	�˻��ᾧ = products["�˻��ᾧ"];
	Price ɽë鷹�ʵ = products["ɽë鷹�ʵ"];


	// ���� �ʺ緭�¼� �ļ۸�
	�ȶ������Ǿ������� = 3;
	int �������� = 50;
	int ���������� = 50;
	�˻��ᾧ���� = 10;
	int ɽë鷹�ʵ���� = 10;


	�ܹ�ͭ�ļ۸� = �ȶ������Ǿ������� * �ȶ������Ǿ���.toCopper() +
		�������� * ����.toCopper() +
		���������� * ������.toCopper() +
		�˻��ᾧ���� * �˻��ᾧ.toCopper() +
		ɽë鷹�ʵ���� * ɽë鷹�ʵ.toCopper();

	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� �ʺ緭�¼� ����Ʒ�б�
	products["�ʺ緭�¼�"] = �²�Ʒ�۸�;
	cout << "�ʺ緭�¼� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** �߲���ʯ **/
	if (products.find("��ˮ��") == products.end() ||
		products.find("����") == products.end() ||
		products.find("����ʯ") == products.end() ||
		products.find("�챦ʯ") == products.end() ||
		products.find("��ĸ��") == products.end() ||
		products.find("��ʯ") == products.end()) {
		cerr << "��Ҫ����� ��ˮ�� ���� ����ʯ �챦ʯ ��ĸ�� ��ʯ �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ��ˮ�� = products["��ˮ��"];
	Price ���� = products["����"];
	Price ����ʯ = products["����ʯ"];
	Price �챦ʯ = products["�챦ʯ"];
	Price ��ĸ�� = products["��ĸ��"];
	Price ��ʯ = products["��ʯ"];

	// ���� �߲���ʯ �ļ۸�
	int ��ˮ������ = 1;
	int �������� = 1;
	int ����ʯ���� = 1;
	int �챦ʯ���� = 1;
	int ��ĸ������ = 1;
	int ��ʯ���� = 1;


	�ܹ�ͭ�ļ۸� = ��ˮ������ * ��ˮ��.toCopper() +
		�������� * ����.toCopper() +
		����ʯ���� * ����ʯ.toCopper() +
		�챦ʯ���� * �챦ʯ.toCopper() +
		��ĸ������ * ��ĸ��.toCopper() +
		��ʯ���� * ��ʯ.toCopper();

	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� �߲���ʯ ����Ʒ�б�
	products["�߲���ʯ"] = �²�Ʒ�۸�;
	cout << "�߲���ʯ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/** ���������Ӱ������ **/
	if (products.find("�����ϵ��ǹ�ӻ�") == products.end() ||
		products.find("ԭ��½֮��") == products.end() ||
		products.find("����֮��") == products.end() ||
		products.find("�ʺ緭�¼�") == products.end() ||
		products.find("�߲���ʯ") == products.end()) {
		cerr << "��Ҫ����� �����ϵ��ǹ�ӻ� ԭ��½֮�� ����֮�� �ʺ緭�¼� �߲���ʯ �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price �����ϵ��ǹ�ӻ� = products["�����ϵ��ǹ�ӻ�"];
	Price ԭ��½֮�� = products["ԭ��½֮��"];
	Price ����֮�� = products["����֮��"];
	Price �ʺ緭�¼� = products["�ʺ緭�¼�"];
	Price �߲���ʯ = products["�߲���ʯ"];

	// ���� ���������Ӱ������ �ļ۸�
	int �����ϵ��ǹ�ӻ����� = 1;
	int ԭ��½֮������ = 8;
	int ����֮������ = 100;
	int �ʺ緭�¼����� = 3;
	int �߲���ʯ���� = 5;

	�ܹ�ͭ�ļ۸� =
		�����ϵ��ǹ�ӻ����� * �����ϵ��ǹ�ӻ�.toCopper() +
		ԭ��½֮������ * ԭ��½֮��.toCopper() +
		����֮������ * ����֮��.toCopper() +
		�ʺ緭�¼����� * �ʺ緭�¼�.toCopper() +
		�߲���ʯ���� * �߲���ʯ.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ���������Ӱ������ ����Ʒ�б�
	products["���������Ӱ������"] = �²�Ʒ�۸�;
	cout << "���������Ӱ������ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** ���� **/
	if (products.find("����ʯ") == products.end()) {
		cerr << "��Ҫ����� ����ʯ �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ����ʯ = products["����ʯ"];


	// ���� ���� �ļ۸�
	int ����ʯ���� = 3;


	�ܹ�ͭ�ļ۸� =
		����ʯ���� * ����ʯ.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ���� ����Ʒ�б�
	products["����"] = �²�Ʒ�۸�;
	cout << "���� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** ͭ�� **/
	if (products.find("ͭ��ʯ") == products.end()) {
		cerr << "��Ҫ����� ͭ��ʯ �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ͭ��ʯ = products["ͭ��ʯ"];


	// ���� ͭ�� �ļ۸�
	int ͭ��ʯ���� = 3;


	�ܹ�ͭ�ļ۸� =
		ͭ��ʯ���� * ͭ��ʯ.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ͭ�� ����Ʒ�б�
	products["ͭ��"] = �²�Ʒ�۸�;
	cout << "ͭ�� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** ���� **/
	if (products.find("����ʯ") == products.end()) {
		cerr << "��Ҫ����� ����ʯ �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ����ʯ = products["����ʯ"];


	// ���� ���� �ļ۸�
	int ����ʯ���� = 3;


	�ܹ�ͭ�ļ۸� =
		����ʯ���� * ����ʯ.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ���� ����Ʒ�б�
	products["����"] = �²�Ʒ�۸�;
	cout << "���� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** ˫�����¼� **/
	if (products.find("��ɫԴ������") == products.end() ||
		products.find("ӳɽ��") == products.end() ||
		products.find("ˮ�ɻ�") == products.end()) {
		cerr << "��Ҫ����� ��ɫԴ������ ӳɽ�� ˮ�ɻ��ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	��ɫԴ������ = products["��ɫԴ������"];
	Price ӳɽ�� = products["ӳɽ��"];
	Price ˮ�ɻ� = products["ˮ�ɻ�"];

	// ���� ˫�����¼� �ļ۸�
	��ɫԴ���������� = 3;
	int ӳɽ������ = 20;
	int ˮ�ɻ����� = 20;

	�ܹ�ͭ�ļ۸� =
		��ɫԴ���������� * ��ɫԴ������.toCopper() +
		ӳɽ������ * ӳɽ��.toCopper() +
		ˮ�ɻ����� * ˮ�ɻ�.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ˫�����¼� ����Ʒ�б�
	products["˫�����¼�"] = �²�Ʒ�۸�;
	cout << "˫�����¼� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** �Ͻ� **/
	if (products.find("����") == products.end() ||
		products.find("ͭ��") == products.end() ||
		products.find("����") == products.end() ||
		products.find("˫�����¼�") == products.end()) {
		cerr << "��Ҫ����� ���� ͭ�� ���� ˫�����¼� �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ���� = products["����"];
	Price ͭ�� = products["ͭ��"];
	Price ���� = products["����"];
	Price ˫�����¼� = products["˫�����¼�"];

	// ���� �Ͻ� �ļ۸�
	int �������� = 8;
	int ͭ������ = 1;
	int �������� = 1;
	int ˫�����¼����� = 1;

	�ܹ�ͭ�ļ۸� =
		�������� * ����.toCopper() +
		ͭ������ * ͭ��.toCopper() +
		�������� * ����.toCopper() +
		˫�����¼����� * ˫�����¼�.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� �Ͻ� ����Ʒ�б�
	products["�Ͻ�"] = �²�Ʒ�۸�;
	cout << "�Ͻ� �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	/** ��������³�ʯ **/
	if (products.find("���³�ʯ") == products.end() ||
		products.find("����ʯ��") == products.end() ||
		products.find("�Ͻ�") == products.end()) {
		cerr << "��Ҫ����� ���³�ʯ ����ʯ�� �Ͻ� �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ���³�ʯ = products["���³�ʯ"];
	Price ����ʯ�� = products["����ʯ��"];
	Price �Ͻ� = products["�Ͻ�"];

	// ���� ��������³�ʯ �ļ۸�
	int ���³�ʯ���� = 1;
	int ����ʯ������ = 20;
	int �Ͻ����� = 10;

	�ܹ�ͭ�ļ۸� =
		���³�ʯ���� * ���³�ʯ.toCopper() +
		����ʯ������ * ����ʯ��.toCopper() +
		�Ͻ����� * �Ͻ�.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ��������³�ʯ ����Ʒ�б�
	products["��������³�ʯ"] = �²�Ʒ�۸�;
	cout << "��������³�ʯ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;

	/** ���������³�ʯ **/
	if (products.find("��������³�ʯ") == products.end() ||
		products.find("����ʯ��") == products.end() ||
		products.find("�Ͻ�") == products.end()) {
		cerr << "��Ҫ����� ���³�ʯ ����ʯ�� �Ͻ� �ļ۸�\n";
		return;
	}

	// ��ȡ��֪��Ʒ�ļ۸�
	Price ��������³�ʯ = products["��������³�ʯ"];
	����ʯ�� = products["����ʯ��"];
	�Ͻ� = products["�Ͻ�"];

	// ���� ���������³�ʯ �ļ۸�
	int ��������³�ʯ���� = 1;
	����ʯ������ = 30;
	�Ͻ����� = 30;

	�ܹ�ͭ�ļ۸� =
		��������³�ʯ���� * ���³�ʯ.toCopper() +
		����ʯ������ * ����ʯ��.toCopper() +
		�Ͻ����� * �Ͻ�.toCopper();


	�²�Ʒ�۸� = Price::fromCopper(�ܹ�ͭ�ļ۸�);

	// ��� ���������³�ʯ ����Ʒ�б�
	products["���������³�ʯ"] = �²�Ʒ�۸�;
	cout << "���������³�ʯ �ļ۸����Ϊ��" << �²�Ʒ�۸� << endl;


	// ���浽�ļ�
	saveProducts(products, fileName);


}
int main() {
	std::string fileName = "products.txt";
	std::unordered_map<std::string, Price> products;

	// �������е���Ʒ����
	loadProducts(products, fileName);

	int choice;
	do {
		std::cout << "\n��Ʒ����ϵͳ��\n";
		std::cout << "1. �����Ʒ\n";
		std::cout << "2. �鿴��Ʒ\n";
		std::cout << "3. ������Ʒ\n";
		std::cout << "4. ɾ����Ʒ\n";
		std::cout << "5. ����߼����ϵļ۸����\n";
		std::cout << "6. ���沢�˳�\n";
		std::cout << "������ѡ��1-6����";
		std::cin >> choice;

		switch (choice) {
		case 1:
			addProduct(products, fileName);
			break;
		case 2:
			viewProducts(products);
			break;
		case 3:
			updateProduct(products, fileName);
			break;
		case 4:
			deleteProduct(products, fileName);
			break;
		case 5:
			calculateAndAddProduct(products, fileName);
			break;
		case 6:
			saveProducts(products, fileName);
			std::cout << "�˳�ϵͳ��\n";
			break;
		default:
			std::cout << "��Ч��ѡ�����������롣\n";
			break;
		}
	} while (choice != 6);

	return 0;
}

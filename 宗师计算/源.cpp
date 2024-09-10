#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
// 价格结构体定义
struct Price {
	int gold;   // 金
	int silver; // 银
	int copper; // 铜

	int toCopper() const;
	static Price fromCopper(int totalCopper);
};

// 格式化输出价格
ostream& operator<<(ostream& os, const Price& p);

// 添加商品函数声明
void addProduct(unordered_map<string, Price>& products, const string& fileName);
void viewProducts(const unordered_map<string, Price>& products);
void updateProduct(unordered_map<string, Price>& products, const string& fileName);
void deleteProduct(unordered_map<string, Price>& products, const string& fileName);
void saveProducts(const unordered_map<string, Price>& products, const string& fileName);
void loadProducts(unordered_map<string, Price>& products, const string& fileName);

// 价格结构体成员函数定义
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

// 格式化输出价格
ostream& operator<<(ostream& os, const Price& p) {
	os << p.gold << "金 " << p.silver << "银 " << p.copper << "铜";
	return os;
}

// 添加商品
void addProduct(unordered_map<string, Price>& products, const string& fileName) {
	string name;
	Price price;
	cout << "请输入商品名称：";
	cin.ignore();  // 忽略换行符
	getline(cin, name);
	cout << "请输入 " << name << " 的价格（金 银 铜）：";
	cin >> price.gold >> price.silver >> price.copper;
	products[name] = price;
	cout << "商品添加成功。\n";
	saveProducts(products, fileName);  // 保存到文件
}

// 查看商品
void viewProducts(const unordered_map<string, Price>& products) {
	if (products.empty()) {
		cout << "没有商品记录。\n";
		return;
	}
	cout << "商品列表：\n";
	for (const auto& item : products) {
		cout << item.first << " : " << item.second << endl;
	}
}

// 更新商品
void updateProduct(unordered_map<string, Price>& products, const string& fileName) {
	string name;
	cout << "请输入要更新的商品名称：";
	cin.ignore();  // 忽略换行符
	getline(cin, name);

	auto it = products.find(name);
	if (it == products.end()) {
		cout << "商品未找到。\n";
		return;
	}

	Price newPrice;
	cout << "请输入新价格（金 银 铜）：";
	cin >> newPrice.gold >> newPrice.silver >> newPrice.copper;
	it->second = newPrice;
	cout << "商品价格更新成功。\n";
	saveProducts(products, fileName);  // 保存到文件
}

// 删除商品
void deleteProduct(unordered_map<string, Price>& products, const string& fileName) {
	string name;
	cout << "请输入要删除的商品名称：";
	cin.ignore();  // 忽略换行符
	getline(cin, name);

	auto it = products.find(name);
	if (it == products.end()) {
		cout << "商品未找到。\n";
		return;
	}

	products.erase(it);
	cout << "商品已删除。\n";
	saveProducts(products, fileName);  // 保存到文件
}

// 保存商品信息到文件
void saveProducts(const unordered_map<string, Price>& products, const string& fileName) {
	ofstream outFile(fileName);
	if (outFile.is_open()) {
		for (const auto& item : products) {
			outFile << item.first << " " << item.second.toCopper() << endl;
		}
		outFile.close();
		cout << "商品信息已保存。\n";
	}
	else {
		cerr << "无法打开文件进行写入。\n";
	}
}

// 从文件加载商品信息
void loadProducts(unordered_map<string, Price>& products, const string& fileName) {
	ifstream inFile(fileName);
	if (inFile.is_open()) {
		string name;
		int totalCopper;
		while (inFile >> name >> totalCopper) {
			products[name] = Price::fromCopper(totalCopper);
		}
		inFile.close();
		cout << "商品信息已加载。\n";
	}
	else {
		cerr << "没有找到价格文件，将创建新的文件。" << endl;
	}
}
// 计算价格并添加到商品列表
void calculateAndAddProduct(unordered_map<string, Price>& products, const string& fileName)
{
	/** 胚芽皮革油 **/
	// 确保商品价格已经加载
	if (products.find("大米") == products.end() || products.find("玉米") == products.end() || products.find("黑色源晶精华") == products.end()) {
		cerr << "需要先添加大米、玉米和黑色源晶精华的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 大米 = products["大米"];
	Price 玉米 = products["玉米"];
	Price 黑色源晶精华 = products["黑色源晶精华"];

	// 计算胚芽皮革油的价格
	int 黑色源晶精华数量 = 3;
	int 大米数量 = 20;
	int 玉米数量 = 20;

	int 总共铜的价格 = 黑色源晶精华数量 * 黑色源晶精华.toCopper() +
		大米数量 * 大米.toCopper() +
		玉米数量 * 玉米.toCopper();

	Price 新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加胚芽皮革油到商品列表
	products["胚芽皮革油"] = 新产品价格;
	cout << "胚芽皮革油的价格计算为：" << 新产品价格 << endl;


	/** 皮革 **/
	if (products.find("生皮") == products.end()) {
		cerr << "需要先添加皮革的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 生皮 = products["生皮"];


	// 计算 皮革 的价格
	int 生皮数量 = 3;


	总共铜的价格 = 生皮数量 * 生皮.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 皮革 到商品列表
	products["皮革"] = 新产品价格;
	cout << "皮革的价格计算为：" << 新产品价格 << endl;

	/** 优质皮革 **/
	if (products.find("皮革") == products.end() || products.find("胚芽皮革油") == products.end()) {
		cerr << "需要先添加皮革跟胚芽皮革油的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 皮革 = products["皮革"];
	Price 胚芽皮革油 = products["胚芽皮革油"];


	// 计算优质皮革的价格
	int 皮革数量 = 10;
	int 胚芽皮革油数量 = 1;


	总共铜的价格 = 皮革数量 * 皮革.toCopper() +
		胚芽皮革油数量 * 胚芽皮革油.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加优质皮革到商品列表
	products["优质皮革"] = 新产品价格;
	cout << "优质皮革的价格计算为：" << 新产品价格 << endl;

	/* 杂质皮革油 */
	if (products.find("黑色源晶精华") == products.end() || products.find("花生") == products.end() || products.find("小麦") == products.end() || products.find("红色珊瑚草") == products.end()) {
		cerr << "需要先添加黑色源晶精华 花生 小麦 红色珊瑚草的价格。\n";
		return;
	}
	// 获取已知商品的价格
	黑色源晶精华 = products["黑色源晶精华"];
	Price 花生 = products["花生"];
	Price 小麦 = products["小麦"];
	Price 红色珊瑚草 = products["红色珊瑚草"];

	// 计算杂质皮革油的价格
	黑色源晶精华数量 = 5;
	int 花生数量 = 30;
	int 小麦数量 = 30;
	int 红色珊瑚草数量 = 20;

	总共铜的价格 = 黑色源晶精华数量 * 黑色源晶精华.toCopper() +
		花生数量 * 花生.toCopper() +
		小麦数量 * 小麦.toCopper() +
		红色珊瑚草数量 * 红色珊瑚草.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 优质皮革 到商品列表
	products["杂质皮革油"] = 新产品价格;
	cout << "杂质皮革油 的价格计算为：" << 新产品价格 << endl;

	/* 真皮皮革 */
	if (products.find("庭院的神秘粉末") == products.end() || products.find("杂质皮革油") == products.end() || products.find("优质皮革") == products.end()) {
		cerr << "需要先添加 庭院的神秘粉末 杂质皮革油 优质皮革 的价格。\n";
		return;
	}
	// 获取已知商品的价格
	Price 庭院的神秘粉末 = products["庭院的神秘粉末"];
	Price 杂质皮革油 = products["杂质皮革油"];
	Price 优质皮革 = products["优质皮革"];

	// 计算 真皮皮革 的价格
	int 庭院的神秘粉末数量 = 5;
	int 杂质皮革油数量 = 1;
	int 优质皮革数量 = 10;


	总共铜的价格 = 庭院的神秘粉末数量 * 庭院的神秘粉末.toCopper() +
		杂质皮革油数量 * 杂质皮革油.toCopper() +
		优质皮革数量 * 优质皮革.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 真皮皮革 到商品列表
	products["真皮皮革"] = 新产品价格;
	cout << "真皮皮革 的价格计算为：" << 新产品价格 << endl;

	/** 亚纳锭 **/
	if (products.find("亚钠矿石") == products.end()) {
		cerr << "需要先添加 亚钠矿石 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 亚钠矿石 = products["亚钠矿石"];


	// 计算 亚纳锭 的价格
	int 亚钠矿石数量 = 3;


	总共铜的价格 = 亚钠矿石数量 * 亚钠矿石.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 亚纳锭 到商品列表
	products["亚纳锭"] = 新产品价格;
	cout << "亚纳锭 的价格计算为：" << 新产品价格 << endl;

	/* 柔韧的真皮皮革 */
	if (products.find("真皮皮革") == products.end() || products.find("亚纳锭") == products.end() || products.find("稳定的龙骨精华") == products.end() || products.find("烈火原木") == products.end()) {
		cerr << "需要先添加 真皮皮革 亚纳锭 稳定的龙骨精华 烈火原木 的价格。\n";
		return;
	}
	// 获取已知商品的价格
	Price 真皮皮革 = products["真皮皮革"];
	Price 亚纳锭 = products["亚纳锭"];
	Price 稳定的龙骨精华 = products["稳定的龙骨精华"];
	Price 烈火原木 = products["烈火原木"];
	// 计算 真皮皮革 的价格
	int 真皮皮革数量 = 10;
	int 亚纳锭数量 = 9;
	int 稳定的龙骨精华数量 = 25;
	int 烈火原木数量 = 6;

	总共铜的价格 = 真皮皮革数量 * 真皮皮革.toCopper() +
		亚纳锭数量 * 亚纳锭.toCopper() +
		稳定的龙骨精华数量 * 稳定的龙骨精华.toCopper() +
		烈火原木数量 * 烈火原木.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 柔韧的真皮皮革 到商品列表
	products["柔韧的真皮皮革"] = 新产品价格;
	cout << "柔韧的真皮皮革 的价格计算为：" << 新产品价格 << endl;

	/* 五彩皮革油 */
	if (products.find("粟米") == products.end() ||
		products.find("长脑参") == products.end() ||
		products.find("稳定的龙骨精华") == products.end() ||
		products.find("浪花结晶") == products.end() ||
		products.find("椰子") == products.end()
		) {
		cerr << "需要先添加 粟米 长脑参 稳定的龙骨精华 浪花结晶 椰子 的价格。\n";
		return;
	}
	// 获取已知商品的价格
	Price 粟米 = products["粟米"];
	Price 长脑参 = products["长脑参"];
	稳定的龙骨精华 = products["稳定的龙骨精华"];
	Price 浪花结晶 = products["浪花结晶"];
	Price 椰子 = products["椰子"];
	// 计算 五彩皮革油 的价格
	int 粟米数量 = 50;
	int 长脑参数量 = 50;
	稳定的龙骨精华数量 = 3;
	int 浪花结晶数量 = 10;
	int 椰子数量 = 10;

	总共铜的价格 = 粟米数量 * 粟米.toCopper() +
		长脑参数量 * 长脑参.toCopper() +
		稳定的龙骨精华数量 * 稳定的龙骨精华.toCopper() +
		浪花结晶数量 * 浪花结晶.toCopper() +
		椰子数量 * 椰子.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 五彩皮革油 到商品列表
	products["五彩皮革油"] = 新产品价格;
	cout << "五彩皮革油 的价格计算为：" << 新产品价格 << endl;


	/* 伊弗南的月光庇护 */
	if (products.find("强酸性毒囊") == products.end() ||
		products.find("编制的甲胄") == products.end() ||
		products.find("稳定的龙骨精华") == products.end()
		) {
		cerr << "需要先添加 强酸性毒囊 编制的甲胄 稳定的龙骨精华数量的价格。\n";
		return;
	}
	// 获取已知商品的价格
	Price 强酸性毒囊 = products["强酸性毒囊"];
	Price 编制的甲胄 = products["编制的甲胄"];
	稳定的龙骨精华 = products["稳定的龙骨精华"];
	// 计算 伊弗南的月光庇护 的价格
	int 强酸性毒囊数量 = 4;
	int 编制的甲胄数量 = 4;
	稳定的龙骨精华数量 = 50;

	总共铜的价格 = 强酸性毒囊数量 * 强酸性毒囊.toCopper() +
		编制的甲胄数量 * 编制的甲胄.toCopper() +
		稳定的龙骨精华数量 * 稳定的龙骨精华.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 伊弗南的月光庇护 到商品列表
	products["伊弗南的月光庇护"] = 新产品价格;
	cout << "伊弗南的月光庇护 的价格计算为：" << 新产品价格 << endl;
	// 添加 伊弗南的阳光庇护 到商品列表
	products["伊弗南的阳光庇护"] = 新产品价格;
	cout << "伊弗南的阳光庇护 的价格计算为：" << 新产品价格 << endl;
	// 添加 伊弗南的星光庇护 到商品列表
	products["伊弗南的星光庇护"] = 新产品价格;
	cout << "伊弗南的星光庇护 的价格计算为：" << 新产品价格 << endl;


	/** 防具源晶精华 **/
	if (products.find("防具源晶晶片") == products.end()) {
		cerr << "需要先添加 防具源晶晶片 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 防具源晶晶片 = products["防具源晶晶片"];


	// 计算 防具源晶精华 的价格
	int 防具源晶晶片数量 = 5;


	总共铜的价格 = 防具源晶晶片数量 * 防具源晶晶片.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 防具源晶精华 到商品列表
	products["防具源晶精华"] = 新产品价格;
	cout << "防具源晶精华 的价格计算为：" << 新产品价格 << endl;

	/** 防具强化卷轴 **/
	if (products.find("防具强化菱石") == products.end() ||
		products.find("空卷轴") == products.end()) {
		cerr << "需要先添加 防具强化菱石 空卷轴 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 防具强化菱石 = products["防具强化菱石"];
	Price 空卷轴 = products["空卷轴"];

	// 计算 防具强化卷轴 的价格
	int 防具强化菱石数量 = 1;
	int 空卷轴数量 = 1;


	总共铜的价格 = 防具强化菱石数量 * 防具强化菱石.toCopper() +
		空卷轴数量 * 空卷轴.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 防具强化卷轴 到商品列表
	products["防具强化卷轴"] = 新产品价格;
	cout << "防具强化卷轴 的价格计算为：" << 新产品价格 << endl;


	/************************** 皮甲宗师一套白板 **************************/
	/* 宗师_皮甲头 */
	if (products.find("防具强化卷轴") == products.end() ||
		products.find("防具源晶精华") == products.end() ||
		products.find("伊弗南的月光庇护") == products.end() ||
		products.find("柔韧的真皮皮革") == products.end() ||
		products.find("五彩皮革油") == products.end())
	{
		cerr << "需要先添加 防具强化卷轴 防具源晶精华 伊弗南的月光庇护 柔韧的真皮皮革 五彩皮革油 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 防具强化卷轴 = products["防具强化菱石"];
	Price 防具源晶精华 = products["防具源晶精华"];
	Price 伊弗南的月光庇护 = products["伊弗南的月光庇护"];
	Price 柔韧的真皮皮革 = products["柔韧的真皮皮革"];
	Price 五彩皮革油 = products["五彩皮革油"];

	// 计算 宗师_皮甲头 的价格
	int 防具强化卷轴数量 = 10;
	int 防具源晶精华数量 = 82;
	int 伊弗南的月光庇护数量 = 1;
	int 柔韧的真皮皮革数量 = 11;
	int 五彩皮革油数量 = 35;

	总共铜的价格 = 防具强化卷轴数量 * 防具强化卷轴.toCopper() +
		防具源晶精华数量 * 防具源晶精华.toCopper() +
		伊弗南的月光庇护数量 * 伊弗南的月光庇护.toCopper() +
		柔韧的真皮皮革数量 * 柔韧的真皮皮革.toCopper() +
		五彩皮革油数量 * 五彩皮革油.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 宗师_皮甲头 到商品列表
	products["宗师_皮甲头"] = 新产品价格;
	cout << "宗师_皮甲头 的价格计算为：" << 新产品价格 << endl;


	/*  计算 宗师_皮甲胸 的价格 */
	防具强化卷轴数量 = 10;
	防具源晶精华数量 = 130;
	伊弗南的月光庇护数量 = 1;
	柔韧的真皮皮革数量 = 13;
	五彩皮革油数量 = 35;

	总共铜的价格 = 防具强化卷轴数量 * 防具强化卷轴.toCopper() +
		防具源晶精华数量 * 防具源晶精华.toCopper() +
		伊弗南的月光庇护数量 * 伊弗南的月光庇护.toCopper() +
		柔韧的真皮皮革数量 * 柔韧的真皮皮革.toCopper() +
		五彩皮革油数量 * 五彩皮革油.toCopper();

	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 宗师_皮甲 到商品列表
	products["宗师_皮甲胸"] = 新产品价格;
	cout << "宗师_皮甲胸 的价格计算为：" << 新产品价格 << endl;


	/* 计算 宗师_皮甲腰带 的价格 */
	防具强化卷轴数量 = 10;
	防具源晶精华数量 = 66;
	伊弗南的月光庇护数量 = 1;
	柔韧的真皮皮革数量 = 9;
	五彩皮革油数量 = 35;

	总共铜的价格 = 防具强化卷轴数量 * 防具强化卷轴.toCopper() +
		防具源晶精华数量 * 防具源晶精华.toCopper() +
		伊弗南的月光庇护数量 * 伊弗南的月光庇护.toCopper() +
		柔韧的真皮皮革数量 * 柔韧的真皮皮革.toCopper() +
		五彩皮革油数量 * 五彩皮革油.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 宗师_皮甲腰带 到商品列表
	products["宗师_皮甲腰带"] = 新产品价格;
	cout << "宗师_皮甲腰带 的价格计算为：" << 新产品价格 << endl;



	/* 计算 宗师_皮甲手腕 的价格 */
	防具强化卷轴数量 = 10;
	防具源晶精华数量 = 66;
	伊弗南的月光庇护数量 = 1;
	柔韧的真皮皮革数量 = 9;
	五彩皮革油数量 = 35;

	总共铜的价格 = 防具强化卷轴数量 * 防具强化卷轴.toCopper() +
		防具源晶精华数量 * 防具源晶精华.toCopper() +
		伊弗南的月光庇护数量 * 伊弗南的月光庇护.toCopper() +
		柔韧的真皮皮革数量 * 柔韧的真皮皮革.toCopper() +
		五彩皮革油数量 * 五彩皮革油.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 宗师_皮甲手腕 到商品列表
	products["宗师_皮甲手腕"] = 新产品价格;
	cout << "宗师_皮甲手腕 的价格计算为：" << 新产品价格 << endl;


	/* 计算 宗师_皮甲手套 的价格 */
	防具强化卷轴数量 = 10;
	防具源晶精华数量 = 82;
	伊弗南的月光庇护数量 = 1;
	柔韧的真皮皮革数量 = 11;
	五彩皮革油数量 = 35;

	总共铜的价格 = 防具强化卷轴数量 * 防具强化卷轴.toCopper() +
		防具源晶精华数量 * 防具源晶精华.toCopper() +
		伊弗南的月光庇护数量 * 伊弗南的月光庇护.toCopper() +
		柔韧的真皮皮革数量 * 柔韧的真皮皮革.toCopper() +
		五彩皮革油数量 * 五彩皮革油.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 宗师_皮甲腿甲 到商品列表
	products["宗师_皮甲手套"] = 新产品价格;
	cout << "宗师_皮甲手套 的价格计算为：" << 新产品价格 << endl;


	/* 计算 宗师_皮甲腿甲 的价格 */
	防具强化卷轴数量 = 10;
	防具源晶精华数量 = 97;
	伊弗南的月光庇护数量 = 1;
	柔韧的真皮皮革数量 = 12;
	五彩皮革油数量 = 35;

	总共铜的价格 = 防具强化卷轴数量 * 防具强化卷轴.toCopper() +
		防具源晶精华数量 * 防具源晶精华.toCopper() +
		伊弗南的月光庇护数量 * 伊弗南的月光庇护.toCopper() +
		柔韧的真皮皮革数量 * 柔韧的真皮皮革.toCopper() +
		五彩皮革油数量 * 五彩皮革油.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 宗师_皮甲腿甲 到商品列表
	products["宗师_皮甲腿甲"] = 新产品价格;
	cout << "宗师_皮甲腿甲 的价格计算为：" << 新产品价格 << endl;


	/* 计算 宗师_皮甲鞋子 的价格 */
	防具强化卷轴数量 = 10;
	防具源晶精华数量 = 82;
	伊弗南的月光庇护数量 = 1;
	柔韧的真皮皮革数量 = 11;
	五彩皮革油数量 = 35;

	总共铜的价格 = 防具强化卷轴数量 * 防具强化卷轴.toCopper() +
		防具源晶精华数量 * 防具源晶精华.toCopper() +
		伊弗南的月光庇护数量 * 伊弗南的月光庇护.toCopper() +
		柔韧的真皮皮革数量 * 柔韧的真皮皮革.toCopper() +
		五彩皮革油数量 * 五彩皮革油.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 宗师_皮甲鞋子 到商品列表
	products["宗师_皮甲鞋子"] = 新产品价格;
	cout << "宗师_皮甲鞋子 的价格计算为：" << 新产品价格 << endl;



	/** 银月之华 **/
	if (products.find("银月之尘") == products.end()) {
		cerr << "需要先添加 银月之尘 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 银月之尘 = products["银月之尘"];


	// 计算 银月之华 的价格
	int 银月之尘数量 = 45;


	总共铜的价格 = 银月之尘数量 * 银月之尘.toCopper();

	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 银月之华 到商品列表
	products["银月之华"] = 新产品价格;
	cout << "银月之华 的价格计算为：" << 新产品价格 << endl;

	/** 彩虹翻新剂 **/
	if (products.find("稳定的龙骨精华") == products.end() ||
		products.find("姜黄") == products.end() ||
		products.find("仙人掌") == products.end() ||
		products.find("浪花结晶") == products.end() ||
		products.find("山毛榉果实") == products.end()) {
		cerr << "需要先添加 稳定的龙骨精华 姜黄 仙人掌 浪花结晶 山毛榉果实 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	稳定的龙骨精华 = products["稳定的龙骨精华"];
	Price 姜黄 = products["姜黄"];
	Price 仙人掌 = products["仙人掌"];
	浪花结晶 = products["浪花结晶"];
	Price 山毛榉果实 = products["山毛榉果实"];


	// 计算 彩虹翻新剂 的价格
	稳定的龙骨精华数量 = 3;
	int 姜黄数量 = 50;
	int 仙人掌数量 = 50;
	浪花结晶数量 = 10;
	int 山毛榉果实数量 = 10;


	总共铜的价格 = 稳定的龙骨精华数量 * 稳定的龙骨精华.toCopper() +
		姜黄数量 * 姜黄.toCopper() +
		仙人掌数量 * 仙人掌.toCopper() +
		浪花结晶数量 * 浪花结晶.toCopper() +
		山毛榉果实数量 * 山毛榉果实.toCopper();

	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 彩虹翻新剂 到商品列表
	products["彩虹翻新剂"] = 新产品价格;
	cout << "彩虹翻新剂 的价格计算为：" << 新产品价格 << endl;

	/** 七彩钻石 **/
	if (products.find("紫水晶") == products.end() ||
		products.find("黄玉") == products.end() ||
		products.find("蓝宝石") == products.end() ||
		products.find("红宝石") == products.end() ||
		products.find("祖母绿") == products.end() ||
		products.find("钻石") == products.end()) {
		cerr << "需要先添加 紫水晶 黄玉 蓝宝石 红宝石 祖母绿 钻石 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 紫水晶 = products["紫水晶"];
	Price 黄玉 = products["黄玉"];
	Price 蓝宝石 = products["蓝宝石"];
	Price 红宝石 = products["红宝石"];
	Price 祖母绿 = products["祖母绿"];
	Price 钻石 = products["钻石"];

	// 计算 七彩钻石 的价格
	int 紫水晶数量 = 1;
	int 黄玉数量 = 1;
	int 蓝宝石数量 = 1;
	int 红宝石数量 = 1;
	int 祖母绿数量 = 1;
	int 钻石数量 = 1;


	总共铜的价格 = 紫水晶数量 * 紫水晶.toCopper() +
		黄玉数量 * 黄玉.toCopper() +
		蓝宝石数量 * 蓝宝石.toCopper() +
		红宝石数量 * 红宝石.toCopper() +
		祖母绿数量 * 祖母绿.toCopper() +
		钻石数量 * 钻石.toCopper();

	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 七彩钻石 到商品列表
	products["七彩钻石"] = 新产品价格;
	cout << "七彩钻石 的价格计算为：" << 新产品价格 << endl;


	/** 伊弗尼尔月影·波澜 **/
	if (products.find("伊弗南的星光庇护") == products.end() ||
		products.find("原大陆之书") == products.end() ||
		products.find("银月之华") == products.end() ||
		products.find("彩虹翻新剂") == products.end() ||
		products.find("七彩钻石") == products.end()) {
		cerr << "需要先添加 伊弗南的星光庇护 原大陆之书 银月之华 彩虹翻新剂 七彩钻石 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 伊弗南的星光庇护 = products["伊弗南的星光庇护"];
	Price 原大陆之书 = products["原大陆之书"];
	Price 银月之华 = products["银月之华"];
	Price 彩虹翻新剂 = products["彩虹翻新剂"];
	Price 七彩钻石 = products["七彩钻石"];

	// 计算 伊弗尼尔月影·波澜 的价格
	int 伊弗南的星光庇护数量 = 1;
	int 原大陆之书数量 = 8;
	int 银月之华数量 = 100;
	int 彩虹翻新剂数量 = 3;
	int 七彩钻石数量 = 5;

	总共铜的价格 =
		伊弗南的星光庇护数量 * 伊弗南的星光庇护.toCopper() +
		原大陆之书数量 * 原大陆之书.toCopper() +
		银月之华数量 * 银月之华.toCopper() +
		彩虹翻新剂数量 * 彩虹翻新剂.toCopper() +
		七彩钻石数量 * 七彩钻石.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 伊弗尼尔月影·波澜 到商品列表
	products["伊弗尼尔月影·波澜"] = 新产品价格;
	cout << "伊弗尼尔月影·波澜 的价格计算为：" << 新产品价格 << endl;

	/** 铁锭 **/
	if (products.find("铁矿石") == products.end()) {
		cerr << "需要先添加 铁矿石 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 铁矿石 = products["铁矿石"];


	// 计算 铁锭 的价格
	int 铁矿石数量 = 3;


	总共铜的价格 =
		铁矿石数量 * 铁矿石.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 铁锭 到商品列表
	products["铁锭"] = 新产品价格;
	cout << "铁锭 的价格计算为：" << 新产品价格 << endl;

	/** 铜锭 **/
	if (products.find("铜矿石") == products.end()) {
		cerr << "需要先添加 铜矿石 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 铜矿石 = products["铜矿石"];


	// 计算 铜锭 的价格
	int 铜矿石数量 = 3;


	总共铜的价格 =
		铜矿石数量 * 铜矿石.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 铜锭 到商品列表
	products["铜锭"] = 新产品价格;
	cout << "铜锭 的价格计算为：" << 新产品价格 << endl;

	/** 银锭 **/
	if (products.find("银矿石") == products.end()) {
		cerr << "需要先添加 银矿石 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 银矿石 = products["银矿石"];


	// 计算 银锭 的价格
	int 银矿石数量 = 3;


	总共铜的价格 =
		银矿石数量 * 银矿石.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 银锭 到商品列表
	products["银锭"] = 新产品价格;
	cout << "银锭 的价格计算为：" << 新产品价格 << endl;

	/** 双花翻新剂 **/
	if (products.find("黑色源晶精华") == products.end() ||
		products.find("映山红") == products.end() ||
		products.find("水仙花") == products.end()) {
		cerr << "需要先添加 黑色源晶精华 映山红 水仙花的价格。\n";
		return;
	}

	// 获取已知商品的价格
	黑色源晶精华 = products["黑色源晶精华"];
	Price 映山红 = products["映山红"];
	Price 水仙花 = products["水仙花"];

	// 计算 双花翻新剂 的价格
	黑色源晶精华数量 = 3;
	int 映山红数量 = 20;
	int 水仙花数量 = 20;

	总共铜的价格 =
		黑色源晶精华数量 * 黑色源晶精华.toCopper() +
		映山红数量 * 映山红.toCopper() +
		水仙花数量 * 水仙花.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 双花翻新剂 到商品列表
	products["双花翻新剂"] = 新产品价格;
	cout << "双花翻新剂 的价格计算为：" << 新产品价格 << endl;

	/** 合金锭 **/
	if (products.find("铁锭") == products.end() ||
		products.find("铜锭") == products.end() ||
		products.find("银锭") == products.end() ||
		products.find("双花翻新剂") == products.end()) {
		cerr << "需要先添加 铁锭 铜锭 银锭 双花翻新剂 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 铁锭 = products["铁锭"];
	Price 铜锭 = products["铜锭"];
	Price 银锭 = products["银锭"];
	Price 双花翻新剂 = products["双花翻新剂"];

	// 计算 合金锭 的价格
	int 铁锭数量 = 8;
	int 铜锭数量 = 1;
	int 银锭数量 = 1;
	int 双花翻新剂数量 = 1;

	总共铜的价格 =
		铁锭数量 * 铁锭.toCopper() +
		铜锭数量 * 铜锭.toCopper() +
		银锭数量 * 银锭.toCopper() +
		双花翻新剂数量 * 双花翻新剂.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 合金锭 到商品列表
	products["合金锭"] = 新产品价格;
	cout << "合金锭 的价格计算为：" << 新产品价格 << endl;


	/** 深邃的新月赤石 **/
	if (products.find("新月赤石") == products.end() ||
		products.find("新月石晶") == products.end() ||
		products.find("合金锭") == products.end()) {
		cerr << "需要先添加 新月赤石 新月石晶 合金锭 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 新月赤石 = products["新月赤石"];
	Price 新月石晶 = products["新月石晶"];
	Price 合金锭 = products["合金锭"];

	// 计算 深邃的新月赤石 的价格
	int 新月赤石数量 = 1;
	int 新月石晶数量 = 20;
	int 合金锭数量 = 10;

	总共铜的价格 =
		新月赤石数量 * 新月赤石.toCopper() +
		新月石晶数量 * 新月石晶.toCopper() +
		合金锭数量 * 合金锭.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 深邃的新月赤石 到商品列表
	products["深邃的新月赤石"] = 新产品价格;
	cout << "深邃的新月赤石 的价格计算为：" << 新产品价格 << endl;

	/** 秀丽的新月赤石 **/
	if (products.find("深邃的新月赤石") == products.end() ||
		products.find("新月石晶") == products.end() ||
		products.find("合金锭") == products.end()) {
		cerr << "需要先添加 新月赤石 新月石晶 合金锭 的价格。\n";
		return;
	}

	// 获取已知商品的价格
	Price 深邃的新月赤石 = products["深邃的新月赤石"];
	新月石晶 = products["新月石晶"];
	合金锭 = products["合金锭"];

	// 计算 秀丽的新月赤石 的价格
	int 深邃的新月赤石数量 = 1;
	新月石晶数量 = 30;
	合金锭数量 = 30;

	总共铜的价格 =
		深邃的新月赤石数量 * 新月赤石.toCopper() +
		新月石晶数量 * 新月石晶.toCopper() +
		合金锭数量 * 合金锭.toCopper();


	新产品价格 = Price::fromCopper(总共铜的价格);

	// 添加 秀丽的新月赤石 到商品列表
	products["秀丽的新月赤石"] = 新产品价格;
	cout << "秀丽的新月赤石 的价格计算为：" << 新产品价格 << endl;


	// 保存到文件
	saveProducts(products, fileName);


}
int main() {
	std::string fileName = "products.txt";
	std::unordered_map<std::string, Price> products;

	// 加载现有的商品数据
	loadProducts(products, fileName);

	int choice;
	do {
		std::cout << "\n商品管理系统：\n";
		std::cout << "1. 添加商品\n";
		std::cout << "2. 查看商品\n";
		std::cout << "3. 更新商品\n";
		std::cout << "4. 删除商品\n";
		std::cout << "5. 计算高级材料的价格并添加\n";
		std::cout << "6. 保存并退出\n";
		std::cout << "请输入选择（1-6）：";
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
			std::cout << "退出系统。\n";
			break;
		default:
			std::cout << "无效的选择，请重新输入。\n";
			break;
		}
	} while (choice != 6);

	return 0;
}

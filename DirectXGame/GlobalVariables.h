#pragma once
#include "Vec3.h"
#include <variant>
#include <map>
#include <string>

class GlobalVariables {
private:

	//項目
	struct Item {
		//項目の値
		std::variant<int32_t, float, Vec3> value;
	};
	//グループ
	struct Group {
		std::map<std::string, Item> items;
	};
	//全データ
	std::map<std::string, Group> datas_;

	//グローバル変数の保存先のファイルパス
	const std::string kDirectoryPath = "Resources/GlobalVariables/";


public:
	/// <summary>
	/// グループの作成
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void CreateGroup(const std::string& groupName);
	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update();
	//値のセット(int)
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	//値のセット(float)
	void SetValue(const std::string& groupName, const std::string& key, float value);
	//値のセット(Vec3)
	void SetValue(const std::string& groupName, const std::string& key, const Vec3& value);
	/// <summary>
	/// ファイルの書き出し
	/// </summary>
	/// <param name="groupName">グループ</param>
	void SaveFile(const std::string& groupName);

public:

	static GlobalVariables* GetInstance();

private:
	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables&) = delete;
	GlobalVariables& operator=(const GlobalVariables&) = delete;


};

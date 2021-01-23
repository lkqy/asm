#include "gtest/gtest.h"
#include "src/dsl/integration/integration.h"


struct Item {
    std::unordered_map<std::string, double> model_score;
    double score; // 最终结果放入的位置
};
typedef std::shared_ptr<Item> ItemPtr;

TEST(IntergrationTest, ErrorExp) {

    std::vector<ItemPtr> items;
    // 初始化模型分数
    for (size_t i = 0; i < 100; ++i) {
	auto item = std::make_shared<Item>();
	item->model_score["finish_model"] = 1.0/(i+1);
	item->model_score["download_model"] = 100./(i+100);
	items.push_back(item);
    }

    // 模型名映射到缩写名
    std::unordered_map<std::string, std::string> model_mapping = {
	{"finish_model", "finish"},
	{"download_model", "download"},
    };

    dsl::integration::Intergration<ItemPtr> intergration;
    std::string exp = "finish + download"; //  融合公式

    // 获取模型分数
    dsl::integration::Intergration<ItemPtr>::Input input = [](ItemPtr& item, const std::string& name) -> double {
	return item->model_score[name];
    };

    // 设置最终融合分
    dsl::integration::Intergration<ItemPtr>:: Output output = [](ItemPtr& item, double score) -> void {
	item->score = score;
    };

    // 处理
    auto ret = intergration.process(exp, items, model_mapping, input, output);

    ASSERT_TRUE(ret);
    for (auto & item : items) {
	// 验证是否相等
	ASSERT_EQ(item->score, item->model_score["finish_model"] + item->model_score["download_model"]);
	std::cout<<item->score<<"\n";
    }
}

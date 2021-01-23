#include "../../asm/asm.h"

namespace dsl {
namespace integration {

// 推荐场景下的分数融合, 这里的字段不可以随意添加
DEFINE_STRUCT(RecomItemScore,
          // 统计值
          (std::vector<double>) bid,                 // 广告出价
          (std::vector<double>) cvr,                 // 广告转化率

          // 模型分
          (std::vector<double>) finish,             // 内容是否播放完成
           (std::vector<double>) ctr,                 // 点击率（对于非沉浸式才有效）
           (std::vector<double>) share,             // 分享
           (std::vector<double>) like,             // 点赞
           (std::vector<double>) follow,             // 关注
           (std::vector<double>) download,         // 下载
           (std::vector<double>) comment,             // 阅读评论
           (std::vector<double>) head,             // 点击作者头像
           (std::vector<double>) playtime,         // 播放时长
        // ToDo: 添加其他输出

        // 模型试验
           (std::vector<double>) ab_1,             // 试验
           (std::vector<double>) ab_2,             // 试验
           (std::vector<double>) ab_3,             // 试验
           (std::vector<double>) ab_4,             // 试验
           (std::vector<double>) ab_5,             // 试验
           (std::vector<double>) ab_6,             // 试验
           (std::vector<double>) ab_7,             // 试验
           (std::vector<double>) ab_8,             // 试验
           (std::vector<double>) ab_9,             // 试验

        (std::vector<double>) __result            // 最终分数
) // end



template<typename T>
class Intergration {
public:
    typedef std::function<double(T&, const std::string&)> Input;
    typedef std::function<void(T&, double)> Output;
    /*
     *  expression: 融合公式的表达式，比如"(1+finish*0.3)^1.2 * (1+download*1.2)^0.4"
     *  model_result: 模型预估输出
     *  name_mapping: 模型原始名映射到精简名，比如{{"ffm_test1": "download"}, {"dcn_t1": "finish}}
     *  input: 根据模型名，从T中提取对应模型分
     *  output: 设置融合后的分数
     */
    bool process(const std::string& expression, std::vector<T>& model_result,
                const std::unordered_map<std::string, std::string>& name_mapping,
                Input& input, Output& output) {
	asmjit::Jit<RecomItemScore> jit;
        std::string exp= "__result = " + expression;
        auto ctx = jit.get(exp);
        if (ctx == nullptr) {
            // ToDo: add logging
            return false;
        }

        const size_t size = model_result.size();

        RecomItemScore item_score;
        // ToDo: 移到外面，减少无效计算
        std::unordered_map<std::string, std::vector<double>*> fields;
	asmjit::for_each_address(item_score, [&](auto&& field_name, char* address) {
                fields[field_name] = (std::vector<double>*) address;
        });

        // 绑定所有数据
        for (auto & it : name_mapping) {
            auto iit = fields.find(it.second);
            if (iit != fields.end()) {
                auto& values = *(iit->second);
                // 绑定数据
                values.resize(size);
                for (size_t i = 0; i < size; ++i) {
                    // Tip: 这里有字符串查找，可能有性能瓶颈，长期要优化传入的数据结构
                    values[i] = input(model_result[i], it.first);;
                }
            }
        }

	ctx->eval(item_score);
        if (item_score.__result.size() != size) {
            // ToDo: add logging
            return false;
        }
        for (size_t i = 0; i < size; ++i) {
            double result = item_score.__result[i];
            output(model_result[i], result);
        }
        return true;
    }
};


} // namespace integration
} // namespace dsl

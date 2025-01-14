#include "ema.h"
#include "grad.h"


void update_average(std::shared_ptr<torch::nn::Module> model_tgt, std::shared_ptr<torch::nn::Module> model_src,
                    double beta) {

    // turn off gradient calculation
    toggle_grad(model_tgt, false);
    toggle_grad(model_src, false);

    auto param_dict_src = model_src->named_parameters();
    for (auto kv: model_tgt->named_parameters()) {
        auto p_name = kv.key();
        auto p_tgt = kv.value();
        //std::cout << p_name << std::endl;
        auto p_src = param_dict_src[p_name];
        p_tgt.copy_(beta * p_tgt + (1. - beta) * p_src);
    }

    toggle_grad(model_tgt, true);
    toggle_grad(model_src, true);
}
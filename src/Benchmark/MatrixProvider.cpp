#include "MatrixProvider.h"
#include <iostream>

namespace BlasBooster {

template <typename T>
std::vector<T> as_vector(ptree const& pt, ptree::key_type const& key)
{
    std::vector<T> r;
    for (auto& item : pt.get_child(key))
        r.push_back(item.second.get_value<T>());
    return r;
}

MatrixProvider::MatrixProvider(ptree const& tree)
{
    for (auto&& name_leaf : tree) {
        for (auto&& type_leaf : name_leaf.second) {
            if (type_leaf.first == "DiagonalBand") {

            	auto&& dim_list = as_vector<size_t>(type_leaf.second, "dimension");
            	auto&& band_width_list = as_vector<size_t>(type_leaf.second, "band_width");
            	auto&& value = type_leaf.second.get<double>("value");

            	for (auto&& dim : dim_list) {
                	for (auto&& band_width : band_width_list) {
                        Matrix<Dense, double> matrix(dim, dim, AllFiller<double>(0.0));
                        for (size_t b = 0; b != band_width; ++b) {
                            for (size_t i = 0; i != dim-b; ++i) {
                                matrix(i+b, i) = value;
                                matrix(i, i+b) = value;
                            }
                        }
                        matrix_set[name_leaf.first].push_back(matrix);
                	}
            	}
            } else if (type_leaf.first == "EqualTo") {
            	auto&& source = matrix_set.at(type_leaf.second.get_value<std::string>());
                matrix_set[name_leaf.first].assign(source.begin(), source.end());
            } else {
            	std::runtime_error("Unknown matrix_set type.");
            }
        }
    }
}

} // namespace BlasBooster

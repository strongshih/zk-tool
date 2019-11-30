#include "libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp"
#include "libsnark/common/default_types/r1cs_ppzksnark_pp.hpp"
#include "libsnark/gadgetlib1/pb_variable.hpp"
#include "libsnark/gadgetlib1/gadgets/hashes/sha256/sha256_gadget.hpp"
#include "libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp"
#include "libsnark/gadgetlib1/gadgets/basic_gadgets.hpp"

using namespace libsnark;
using namespace std;

// Constraint Circuits look like
//
// 18 -------------------\
//                        (<)---------------
//        _______________/                  \
//       |                                   \
// Age -------\                               \
//             (concat)--(hash)--\              (verify)
// Password --/                   \           /
//                                 (equal)---/
// hashed_value ------------------/
//

#define CONSTRAINTS() /* variable initialization for hash part*/ \
	vector<pb_variable<FieldT> > my_age_(SHA256_digest_size); \
    for (int i = 0; i < 256; i++) { \
        my_age_[i].allocate(pb, "padding"); \
    } \
    pb_variable<FieldT> my_age; \
    my_age.allocate(pb, "my_age"); \
    pb_variable<FieldT> padding; \
    padding.allocate(pb, "padding"); \
    pb.val(padding) = FieldT::zero(); \
    pb_variable_array<FieldT> vec(my_age_.begin(), my_age_.end()); \
	\
	/* hash( age | password ) = hashed_value */ \
    digest_variable<FieldT> left(pb, SHA256_digest_size, vec, padding, "left"); \
    digest_variable<FieldT> right(pb, SHA256_digest_size, "right"); \
    digest_variable<FieldT> output(pb, SHA256_digest_size, "output"); \
    sha256_two_to_one_hash_gadget<FieldT> f(pb, left, right, output, "f"); \
    f.generate_r1cs_constraints(); \
	\
	/* variable initialization for age comparison part*/ \
    pb_variable<FieldT> target_age, less, less_or_eq; \
    target_age.allocate(pb, "target_age"); \
    less.allocate(pb, "less"); \
    less_or_eq.allocate(pb, "less_or_eq"); \
    comparison_gadget<FieldT> cmp(pb, 8, target_age, my_age, less, less_or_eq, "cmp"); \
    cmp.generate_r1cs_constraints(); \
	\
	/* target_age = 18 and use < */ \
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(target_age, 1, 18)); \
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(less, 1, FieldT::one())); \
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(less_or_eq, 1, FieldT::one())); \
	\
	/* sum(age_) = age */ \
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(my_age_[0] + my_age_[1] + my_age_[2] + my_age_[3] + my_age_[4] + my_age_[5] + my_age_[6] + my_age_[7] + my_age_[8] + my_age_[9] + my_age_[10] + my_age_[11] + my_age_[12] + my_age_[13] + my_age_[14] + my_age_[15] + my_age_[16] + my_age_[17] + my_age_[18] + my_age_[19] + my_age_[20] + my_age_[21] + my_age_[22] + my_age_[23] + my_age_[24] + my_age_[25] + my_age_[26] + my_age_[27] + my_age_[28] + my_age_[29] + my_age_[30] + my_age_[31] + my_age_[32] + my_age_[33] + my_age_[34] + my_age_[35] + my_age_[36] + my_age_[37] + my_age_[38] + my_age_[39] + my_age_[40] + my_age_[41] + my_age_[42] + my_age_[43] + my_age_[44] + my_age_[45] + my_age_[46] + my_age_[47] + my_age_[48] + my_age_[49] + my_age_[50] + my_age_[51] + my_age_[52] + my_age_[53] + my_age_[54] + my_age_[55] + my_age_[56] + my_age_[57] + my_age_[58] + my_age_[59] + my_age_[60] + my_age_[61] + my_age_[62] + my_age_[63] + my_age_[64] + my_age_[65] + my_age_[66] + my_age_[67] + my_age_[68] + my_age_[69] + my_age_[70] + my_age_[71] + my_age_[72] + my_age_[73] + my_age_[74] + my_age_[75] + my_age_[76] + my_age_[77] + my_age_[78] + my_age_[79] + my_age_[80] + my_age_[81] + my_age_[82] + my_age_[83] + my_age_[84] + my_age_[85] + my_age_[86] + my_age_[87] + my_age_[88] + my_age_[89] + my_age_[90] + my_age_[91] + my_age_[92] + my_age_[93] + my_age_[94] + my_age_[95] + my_age_[96] + my_age_[97] + my_age_[98] + my_age_[99] + my_age_[100] + my_age_[101] + my_age_[102] + my_age_[103] + my_age_[104] + my_age_[105] + my_age_[106] + my_age_[107] + my_age_[108] + my_age_[109] + my_age_[110] + my_age_[111] + my_age_[112] + my_age_[113] + my_age_[114] + my_age_[115] + my_age_[116] + my_age_[117] + my_age_[118] + my_age_[119] + my_age_[120] + my_age_[121] + my_age_[122] + my_age_[123] + my_age_[124] + my_age_[125] + my_age_[126] + my_age_[127], 1, my_age)); \
	\
	/* print info */ \
    printf("Number of constraints for sha256_two_to_one_hash_gadget: %zu\n", pb.num_constraints()); 

typedef libff::Fr<default_r1cs_ppzksnark_pp> FieldT;

// write to file
template<typename T> void writeToFile(char *path, T& obj);

// load from file
template<typename T> T loadFromFile(char *path);

// serialize proving key
void serializeProvingKeyToFile(r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> pk, const char* pk_path);

// deserialize proving key
r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> deserializeProvingKeyFromFile(const char* pk_path);

// serialize verification key
void serializeVerifyKeyToFile(r1cs_ppzksnark_verification_key<default_r1cs_ppzksnark_pp> vk, const char* vk_path);

// deserialize verification key
r1cs_ppzksnark_verification_key<default_r1cs_ppzksnark_pp> deserializeVerifyKeyFromFile(const char* vk_path);

// serialize proof
void serializeProofToFile(r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> proof, const char* proof_path);

// deserialize proof
r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> deserializeProofFromFile(const char* proof_path);

#include "libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp"
#include "libsnark/common/default_types/r1cs_ppzksnark_pp.hpp"
#include "libsnark/gadgetlib1/pb_variable.hpp"
#include "libsnark/gadgetlib1/gadgets/hashes/sha256/sha256_gadget.hpp"
#include "libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp"
#include "libsnark/gadgetlib1/gadgets/basic_gadgets.hpp"
#include <fstream>
#include <iostream>
#include "utils.hpp"
#include <vector>

using namespace libsnark;
using namespace std;

int main(int argc, char **argv) {

	if (argc != 13) {
		cout << "usage: ./offline_proof [PATH_TO_PROVING_KEY] [OUTPUT_PATH_FOR_PROOF] [age] [pass] {8-int-password}" << endl;
		return 0;
	}

	int input_age = atoi(argv[3]);
	char *password = argv[4];

	// Initialize the curve parameters
	default_r1cs_ppzksnark_pp::init_public_params();

    protoboard<FieldT> pb;

	// constraint macro
	CONSTRAINTS();

	// witness
	pb.val(target_age) = FieldT(18);
	pb.val(my_age) = FieldT(input_age);
	pb.val(less) = FieldT::one();
	pb.val(less_or_eq) = FieldT::one();
	for (int i = 0; i < input_age; i++) {
		pb.val(my_age_[i]) = FieldT::one();
	}
	cmp.generate_r1cs_witness();

	libff::bit_vector right_bv;	
	for (int i = 0; i < strlen(password); i++) {
		bool temp = (password[i] == '1' ? true : false);
		right_bv.push_back(temp);
	}
	const libff::bit_vector hash_bv = libff::int_list_to_bits({stoul(argv[5], nullptr, 0), stoul(argv[6], nullptr, 0), stoul(argv[7], nullptr, 0), stoul(argv[8], nullptr, 0), stoul(argv[9], nullptr, 0), stoul(argv[10], nullptr, 0), stoul(argv[11], nullptr, 0), stoul(argv[12], nullptr, 0)}, 32);
	cout << stoul(argv[5], nullptr, 0) << endl;
	cout << stoul(argv[6], nullptr, 0) << endl;
    right.generate_r1cs_witness(right_bv);
    f.generate_r1cs_witness();
	output.generate_r1cs_witness(hash_bv);
	cout << "two_inputs_hash_gadget => Satisfied status: " << pb.is_satisfied() << endl;

	r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> proving_key = deserializeProvingKeyFromFile(argv[1]);

    // Create proof
    const r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> proof1 = r1cs_ppzksnark_prover<default_r1cs_ppzksnark_pp>(
            proving_key, pb.primary_input(), pb.auxiliary_input());

	serializeProofToFile(proof1, argv[2]);
	
	return 0;
}

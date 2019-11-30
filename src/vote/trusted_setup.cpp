#include "libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp"
#include "libsnark/common/default_types/r1cs_ppzksnark_pp.hpp"
#include "libsnark/gadgetlib1/pb_variable.hpp"
#include "libsnark/gadgetlib1/gadgets/hashes/sha256/sha256_gadget.hpp"
#include "libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp"
#include "libsnark/gadgetlib1/gadgets/basic_gadgets.hpp"
#include <fstream>
#include <iostream>
#include "utils.hpp"

using namespace libsnark;
using namespace std;

extern "C" void vote_zk_init(char* proof_key_path, char* verify_key_path) {
	// Initialize the curve parameters
	default_r1cs_ppzksnark_pp::init_public_params();

    protoboard<FieldT> pb;

	// constraint macro 
	CONSTRAINTS();

    // Trusted setup
    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();
    const r1cs_ppzksnark_keypair<default_r1cs_ppzksnark_pp> keypair = r1cs_ppzksnark_generator<default_r1cs_ppzksnark_pp>(constraint_system);
	serializeProvingKeyToFile(keypair.pk, proof_key_path);
	serializeVerifyKeyToFile(keypair.vk, verify_key_path);

	/* debug
	pb.val(target_age) = FieldT(18);
	pb.val(my_age) = FieldT(19);
	pb.val(less) = FieldT::one();
	pb.val(less_or_eq) = FieldT::one();

	for (int i = 0; i < 256; i++) {
		pb.val(my_age_[i]) = FieldT::one();
	}
	for (int i = 19; i < 256; i++) {
		pb.val(my_age_[i]) = FieldT::zero();
	}
	cmp.generate_r1cs_witness();

	const libff::bit_vector right_bv = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1};
	// const libff::bit_vector right_bv = libff::int_list_to_bits({0x04030201, 0x08070605, 0x04030201, 0x08070605, 0x04030201, 0x08070605, 0x04030201, 0x08070605}, 32);
	const libff::bit_vector hash_bv = libff::int_list_to_bits({0x89685f93, 0x59575ef3, 0x2074b361, 0x078ce7a6, 0xc35dff02, 0xe578ba4a, 0xe6f9151e, 0xd066228b}, 32);

	std::vector<FieldT> tmp = left.bits.get_vals(pb);
	std::cout << tmp.size()  << std::endl;
	for (std::vector<FieldT>::const_iterator i = tmp.begin(); i != tmp.end(); ++i) {
    	std::cout << *i;
	}
	std::cout << std::endl;

    right.generate_r1cs_witness(right_bv);

	tmp = right.bits.get_vals(pb);
	std::cout << tmp.size()  << std::endl;
	for (std::vector<FieldT>::const_iterator i = tmp.begin(); i != tmp.end(); ++i) {
    	std::cout << *i;
	}
	std::cout << std::endl;

    f.generate_r1cs_witness();
	output.generate_r1cs_witness(hash_bv);
	cout << "two_inputs_hash_gadget => Satisfied status: " << pb.is_satisfied() << endl;
	*/

	return;
}

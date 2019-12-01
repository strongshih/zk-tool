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

template<typename ppT, typename FieldT>
bool verify_proof(r1cs_ppzksnark_verification_key<ppT> verification_key, r1cs_primary_input<FieldT> primary_input,
        r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> proof) {
    return r1cs_ppzksnark_verifier_strong_IC<default_r1cs_ppzksnark_pp>(verification_key, primary_input, proof);
}

extern "C" int vote_zk_verify (char *verify_key_path, char *proof_path) {
	
	// Initialize the curve parameters
	default_r1cs_ppzksnark_pp::init_public_params();

    protoboard<FieldT> pb;

	// constraint macro
    CONSTRAINTS();

	r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> proof1 = deserializeProofFromFile(proof_path);
	r1cs_ppzksnark_verification_key<default_r1cs_ppzksnark_pp> verify_key = deserializeVerifyKeyFromFile(verify_key_path);
	bool verified1 = verify_proof(verify_key, pb.primary_input(), proof1);
	if (verified1) {
		return 1;
	} else {
		return -1;
	}
}

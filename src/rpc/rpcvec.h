/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPCVEC_H_RPCGEN
#define _RPCVEC_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	u_int vec_len;
	double *vec_val;
} vec;

struct vec_and_num {
	vec vector;
	double number;
};
typedef struct vec_and_num vec_and_num;

#define VEC_PROGRAM 0x23451111
#define VEC_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define AVERAGE 1
extern  double * average_1(vec *, CLIENT *);
extern  double * average_1_svc(vec *, struct svc_req *);
#define MINMAX 2
extern  double * minmax_1(vec *, CLIENT *);
extern  double * minmax_1_svc(vec *, struct svc_req *);
#define PRODUCT 3
extern  vec * product_1(vec_and_num *, CLIENT *);
extern  vec * product_1_svc(vec_and_num *, struct svc_req *);
extern int vec_program_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define AVERAGE 1
extern  double * average_1();
extern  double * average_1_svc();
#define MINMAX 2
extern  double * minmax_1();
extern  double * minmax_1_svc();
#define PRODUCT 3
extern  vec * product_1();
extern  vec * product_1_svc();
extern int vec_program_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_vec (XDR *, vec*);
extern  bool_t xdr_vec_and_num (XDR *, vec_and_num*);

#else /* K&R C */
extern bool_t xdr_vec ();
extern bool_t xdr_vec_and_num ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPCVEC_H_RPCGEN */

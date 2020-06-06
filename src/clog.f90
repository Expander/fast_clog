      subroutine clog(re, im, out_re, out_im) bind(C, name="clog_")
      implicit   none
      double precision, intent(in)  :: re,im
      double precision, intent(out) :: out_re,out_im
      double complex :: l

      l = log(dcmplx(re, im))

      out_re = real(l)
      out_im = imag(l)

      end subroutine

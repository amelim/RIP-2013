(define (problem get-paid3)
  (:domain briefcase-world)
  (:objects home office bank)
  (:init (place home)
	 (place office) (place bank)
	 (object p) (object d) (object b)
	 (at b home) (at p home) (at d home) (in p))
  (:goal (and (at p bank) (at d office) (at b home))))

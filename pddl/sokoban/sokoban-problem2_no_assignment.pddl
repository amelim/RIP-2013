(define (problem sokoban_problem2)
  (:domain sokoban-domain)
  (:objects
      down - direction
      left - direction
      right - direction
      up - direction
      r - robot
      b1 - box
      b2 - box
      s-2-2 - location
      s-2-3 - location
      s-3-2 - location
      s-3-3 - location
      s-3-4 - location
      s-4-2 - location
      s-4-3 - location
      s-4-4 - location
      s-4-5 - location
      s-5-3 - location
      s-5-4 - location
      s-5-5 - location
      s-5-6 - location
      s-5-7 - location
  )
  (:init
     (at r s-2-3)
     (at b1 s-3-3)
     (at b2 s-4-3)
     (empty s-2-2)
     (empty s-3-2)
     (empty s-3-4)
     (empty s-4-2)
     (empty s-4-4)
     (empty s-4-5)
     (empty s-5-3)
     (empty s-5-4)
     (empty s-5-5)
     (empty s-5-6)
     (empty s-5-7)
     (adjacent s-2-2 s-3-2 right)
     (adjacent s-3-2 s-2-2 left)
     (adjacent s-2-3 s-3-3 right)
     (adjacent s-3-3 s-2-3 left)
     (adjacent s-3-2 s-4-2 right)
     (adjacent s-4-2 s-3-2 left)
     (adjacent s-3-3 s-4-3 right)
     (adjacent s-4-3 s-3-3 left)
     (adjacent s-3-4 s-4-4 right)
     (adjacent s-4-4 s-3-4 left)
     (adjacent s-4-3 s-5-3 right)
     (adjacent s-5-3 s-4-3 left)
     (adjacent s-4-4 s-5-4 right)
     (adjacent s-5-4 s-4-4 left)
     (adjacent s-4-5 s-5-5 right)
     (adjacent s-5-5 s-4-5 left)
     (adjacent s-2-2 s-2-3 up)
     (adjacent s-2-3 s-2-2 down)
     (adjacent s-3-2 s-3-3 up)
     (adjacent s-3-3 s-3-2 down)
     (adjacent s-3-3 s-3-4 up)
     (adjacent s-3-4 s-3-3 down)
     (adjacent s-4-2 s-4-3 up)
     (adjacent s-4-3 s-4-2 down)
     (adjacent s-4-3 s-4-4 up)
     (adjacent s-4-4 s-4-3 down)
     (adjacent s-4-4 s-4-5 up)
     (adjacent s-4-5 s-4-4 down)
     (adjacent s-5-3 s-5-4 up)
     (adjacent s-5-4 s-5-3 down)
     (adjacent s-5-4 s-5-5 up)
     (adjacent s-5-5 s-5-4 down)
     (adjacent s-5-5 s-5-6 up)
     (adjacent s-5-6 s-5-5 down)
     (adjacent s-5-6 s-5-7 up)
     (adjacent s-5-7 s-5-6 down)
  )
  (:goal (and
             (not(at r s-2-2))
             (not(at r s-5-7))
			 (not(empty s-2-2))
			 (not(empty s-5-7))
         )
  )
)

(define (domain sokoban-domain)
  (:requirements :typing )
  (:types thing location direction - object
          robot - thing)
  (:predicates (empty ?l - location)
			   (at ?t - thing ?l - location) 
               (adjacent ?from ?to - location ?dir - direction))

  (:action move
    :parameters (?r - robot ?from ?to - location ?dir - direction)
    :precondition (and (at ?r ?from)
				  (empty ?to) 
                  (adjacent ?from ?to ?dir))
    :effect (and (at ?r ?to) 
				 (not (at ?r ?from))
				 (not (empty ?to)) 
             	 (empty ?from))
  )
)

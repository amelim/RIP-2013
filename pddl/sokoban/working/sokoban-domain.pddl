(define (domain sokoban-domain)
  (:requirements :typing )
  (:types thing location direction - object
          robot box - thing)
  (:predicates (empty ?loc - location)
			   (at ?t - thing ?loc - location) 
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

  (:action push
    :parameters (?r - robot 
				 ?b - box 
				 ?rloc ?bloc ?tloc - location 
				 ?dir - direction)
    :precondition (and 	(empty ?tloc)
                   		(at ?r ?rloc) 
						(at ?b ?bloc)
						(adjacent ?rloc ?bloc ?dir)
						(adjacent ?bloc ?tloc ?dir)
						)
    :effect (and 	(at ?r ?bloc) 
              		(at ?b ?tloc) 
				 	(not (at ?r ?rloc))
					(not (at ?b ?bloc)) 
             		(empty ?rloc) 
					(not (empty ?tloc)))
	)
)

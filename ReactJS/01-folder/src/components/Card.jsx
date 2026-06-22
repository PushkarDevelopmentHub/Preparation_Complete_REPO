import React from 'react'

const Card = (props) => {
  console.table(props);
  return (
    <div className='card'>
      <img src="https://images.unsplash.com/photo-1773332585698-cba3c91b73e4?q=80&w=1169&auto=format&fit=crop&ixlib=rb-4.1.0&ixid=M3wxMjA3fDF8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D" alt="" />
       <h1>{props.user}</h1>
       <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Maiores hic optio autem similique omnis et non harum ad tempora aspernatur, a tempore iste enim tenetur cumque in odio atque quia.</p>
       <button>click Here</button>
    </div>
  )
}

export default Card

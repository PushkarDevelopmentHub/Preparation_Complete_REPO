import React from "react";
import { Bookmark } from "lucide-react";
const SecondCard = (props) => {
  return (
    <div className="secondCard">
      <div>
        <div className="top">
          <img
            src={props.brandLogo}
            alt="img"
          />
          <button>
            Save <Bookmark size={10} />{" "}
          </button>
        </div>
      </div>
      <div className="center">
        <h3>
          {props.company} <span>{props.datePosted}</span>{" "}
        </h3>
        <h2> {props.post} </h2>
        <div>
          <h4>{props.tag1}</h4>
          <h4>{props.tag2}</h4>
        </div>
      </div>
      <div className="bottom">
        <div>
          <h3>{props.pay}</h3>
          <p>Mumbai</p>

        </div>
          <button>Apply Now</button>
      </div>
    </div>
  );
};

export default SecondCard;
